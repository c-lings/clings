#ifndef CLINGS_KATAS_H
#define CLINGS_KATAS_H

#include "types/types.h"
#include "stdbool.h"

typedef struct kata {
    sized_string_t name;
    sized_string_t path;
} kata_t;

typedef struct kata_list {
    kata_t * katas;
    size_t len;
} kata_list_t;

typedef struct kata_list_parsing_result {
    bool success;
    union {
      kata_list_t kata_list;
        char *error_message;
    };
} kata_list_parsing_result_t;

void free_kata_list(kata_list_t *kata_list);

void push_kata_in_list(kata_t kata, kata_list_t *list);

kata_t no_kata();

#endif //CLINGS_KATAS_H
