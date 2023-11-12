#include "types.h"

sized_string_t new_sized_string(size_t len) {
    sized_string_t s;
    s.str = (char *)calloc(len, sizeof(char));
    if (s.str) {
        s.len = len;
    } else {
        s.len = 0;
    }
    return s;
}

void free_sized_string(sized_string_t string) {
    if (string.str) {
        free(string.str);
        string.str = NULL;
    }
}