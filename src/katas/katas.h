#ifndef CLINGS_KATAS_H
#define CLINGS_KATAS_H

#include "types/types.h"
#include "stdbool.h"

typedef struct Kata Kata;
struct Kata {
    sized_string_t name;
    sized_string_t path;
};

typedef struct KataList KataList;
struct KataList {
    struct Kata * katas;
    size_t len;
};

typedef struct KataListParsingResult KataListParsingResult;
struct KataListParsingResult {
    bool success;
    union {
        KataList kata_list;
        char *error_message;
    };
};

void free_kata_list(KataList *kata_list);

void push_kata_in_list(Kata kata, KataList *list);

Kata no_kata();

#endif //CLINGS_KATAS_H
