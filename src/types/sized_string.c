#include <string.h>
#include "types.h"

sized_string_t new_sized_string(size_t len) {
    sized_string_t string;
    string.str = (char *)calloc(len, sizeof(char));
    if (string.str) {
        string.len = len;
    } else {
        string.len = 0;
    }
    return string;
}

void free_sized_string(sized_string_t * string) {
    if (string->str) {
        free(string->str);
        string->str = NULL;
    }
    string->len = 0;
}

sized_string_t copy_str_to_sized_string(char * str, size_t len) {
    sized_string_t string = new_sized_string(len);
    if(!string.str) {
        return string;
    }
    strncpy(string.str, str, len);
    return string;
}


sized_string_t empty_sized_string(void) {
    return (sized_string_t) {
            .str = NULL,
            .len = 0
    };
}
