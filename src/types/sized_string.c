#include <string.h>
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

void free_sized_string(sized_string_t * string) {
    if (string->str) {
        free(string->str);
        string->str = NULL;
    }
    string->len = 0;
}

sized_string_t copy_str_to_sized_string(char * str, size_t len) {
    sized_string_t s;
    s.str = strncpy((char *)calloc(len, sizeof(char)), str, len);
    s.len = strlen(s.str);
    return s;
}


sized_string_t empty_sized_string() {
    return (sized_string_t) {
            .str = NULL,
            .len = 0
    };
}