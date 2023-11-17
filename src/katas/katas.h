#ifndef CLINGS_KATAS_H
#define CLINGS_KATAS_H


// TODO: extract this to yaml
static const char * kata_folder_path = "../katas/";

static const char * kata_file_names[] = {
        "success.c",
        "compilation_error.c",
        "run_error.c",
        "test_error.c"
};

static const int nb_kata_files = sizeof(kata_file_names) / sizeof(kata_file_names[0]);

#endif //CLINGS_KATAS_H
