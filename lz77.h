#include <stdbool.h>
#include <stdint.h>
#define SEARCH_BUFFER_SIZE     7
#define LOOK_AHEAD_BUFFER_SIZE 6
#define WINDOW_SIZE            (SEARCH_BUFFER_SIZE + LOOK_AHEAD_BUFFER_SIZE)
#define DATA_SIZE              17
#define MATCH_TOKEN            1
#define UNMATCH_TOKEN          0

typedef struct {
	uint32_t longest_match_len;
	int32_t longest_match_index;
} longest_match_t;

typedef struct {
	uint32_t distance;
	uint32_t length;
	uint32_t character;
} lz77_t; // triple (D, L, C), like : (0,0,C)

void init_look_ahead_buffer();
bool shift_window(int skip);
longest_match_t find_match();
void print_lz77_encode_data();
