# LZ77
This is an implementation of the LZ77 algorithm, written in C.

LZ77 is an algorithm that removes redundant and duplicate ddata by replacing them with references.

A reference consists of a triplet (D, L, C), where D is the distance, L is the length of the match, and C is the next character following the matched segment (if any). Using this approach, redundant data is replace with smaller references, which helps reduce the overall data size.

However, for better functionality, minimum and maximum length limits are typically imposed on the matched segment. This is because replacement is not always beneficial; in some cases, the triplet is the same size as the data it replaces, or even larger.

As a result, optimal parameters may vary depending on the specific input data.
