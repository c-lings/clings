#include "katas.h"
#include "../types/types.h"


void free_kata(struct Kata *kata);

void free_kata_list(KataList *kata_list) {
    for (int i = 0; i < kata_list->len; i++) {
        free_kata(&kata_list->katas[i]);
    }
    kata_list->katas = NULL;
}

void free_kata(struct Kata *kata) {
    free_sized_string(kata->name);
    free_sized_string(kata->path);
}

