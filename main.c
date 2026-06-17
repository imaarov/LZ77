#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#define SEARCH_BUFFER_SIZE     7
#define LOOK_AHEAD_BUFFER_SIZE 6
#define WINDOW_SIZE            SEARCH_BUFFER_SIZE + LOOK_AHEAD_BUFFER_SIZE
#define DATA_SIZE              17

typedef struct {
    uint32_t longest_match_len;
    int32_t  longest_match_index;
} longest_match_t;

typedef struct {
    uint32_t distance;
    uint32_t length;
    uint32_t character;
} lz77_t;               // triple (D, L, C), like : (0,0,C)

char data[] = {
    'a', 'b', 'c', 'd', 'a', 'b', 'c',
    'a', 'b', 'c', 'd', 'a', 'b', 'c',
    'x', 'y', 'z'
};

uint32_t window[WINDOW_SIZE] = {0};
uint32_t data_pointer = LOOK_AHEAD_BUFFER_SIZE;
uint32_t window_pointer = SEARCH_BUFFER_SIZE;
lz77_t lz77_encode_data[16];

void init_look_ahead_buffer();
bool shift_window(int skip);
longest_match_t find_match();
void print_lz77_encode_data();

int main() {
    init_look_ahead_buffer();
    uint32_t lz_index = 0;
    while (1) {
        longest_match_t match = find_match();
        if (match.longest_match_index == -1) {
            lz77_t lz;
            lz.character = window[window_pointer];
            lz.length    = match.longest_match_len;
            lz.distance  = 0;
            lz77_encode_data[lz_index++] = lz;
            if (!shift_window(1)) {
                break;
            }
        }else {
            lz77_t lz;
            if (window_pointer + match.longest_match_len == WINDOW_SIZE) {
                lz.character = data[data_pointer];
            }else {
                lz.character = window[window_pointer + match.longest_match_index];
            }
            lz.length    = match.longest_match_len;
            lz.distance  = window_pointer - match.longest_match_index;
            lz77_encode_data[lz_index++] = lz;
            if (!shift_window(match.longest_match_len + 1)) {
                break;
            }
        }
    }

    print_lz77_encode_data();
    return 0;
}

void init_look_ahead_buffer() {
    for (int i = SEARCH_BUFFER_SIZE, j = 0; i < WINDOW_SIZE; i++) {
        window[i] = data[j++];
    }
}

bool shift_window(int skip) {
    if (data_pointer >= DATA_SIZE + LOOK_AHEAD_BUFFER_SIZE) {
        return false;
    }
    for (int i = 0, s = skip; s < WINDOW_SIZE; i++, s++) {
        window[i] = window[s];
    }
    for (int i = skip; i > 0; i--) {
        window[WINDOW_SIZE - i] = data[data_pointer];
        if (data_pointer >= DATA_SIZE + LOOK_AHEAD_BUFFER_SIZE) {
            return false;
        }
        ++data_pointer;
    }
    return true;
}

longest_match_t find_match() {
    int longest_match_len   = 0;
    int longest_match_index = -1;
    int match_len = 0;
    for (int search_index = 0, look_ahead_index = SEARCH_BUFFER_SIZE; 
            search_index < SEARCH_BUFFER_SIZE && look_ahead_index < WINDOW_SIZE; 
            search_index++) {
        int s = search_index;
        int l = look_ahead_index;
        while ((window[s] == window[l]) && (s < SEARCH_BUFFER_SIZE) && (l < WINDOW_SIZE)) {
            ++match_len;
            ++l;
            ++s;
        }
        if (match_len > longest_match_len) {
            longest_match_len   = match_len;
            longest_match_index = search_index;
        }
        match_len = 0;
    }

    longest_match_t match;
    match.longest_match_index = longest_match_index;
    match.longest_match_len   = longest_match_len;
    return match;
}

void print_lz77_encode_data() {
    for (int i = 0; i < DATA_SIZE; i++) {
        printf("D: %u L: %u C: %c\n", lz77_encode_data[i].distance, lz77_encode_data[i].length, lz77_encode_data[i].character);
    }
}
