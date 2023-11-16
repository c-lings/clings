#ifndef CLINGS_KATAS_H
#define CLINGS_KATAS_H

#include "../types/types.h"

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

void free_kata_list(KataList *kata_list);

static const char * kata_folder_path = "../katas/";

static const char * kata_file_names[] = {
        "success.c",
        "compilation_error.c",
        "run_error.c",
        "test_error.c"
};

static const int nb_kata_files = sizeof(kata_file_names) / sizeof(kata_file_names[0]);

#endif //CLINGS_KATAS_H
