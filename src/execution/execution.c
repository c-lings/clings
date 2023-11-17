#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "execution.h"

kata_status run_kata(const int kata_index, sized_string_t result_buffer) {
    // Validate index
    if (
            kata_index < 0 ||
            kata_index >= nb_kata_files ||
            !kata_file_names[kata_index]
        ) {
        strncpy(result_buffer.str, "Invalid kata index", result_buffer.len);
        return KATA_ERROR;
    }

    char compile_command[MAX_PATH_LENGTH];
    char file_path[MAX_PATH_LENGTH];

    // Create file path
    snprintf(file_path, MAX_PATH_LENGTH, "%s%s", kata_folder_path, kata_file_names[kata_index]);
    // TODO: check if file exists

    // Create compile command
    snprintf(compile_command, MAX_PATH_LENGTH, COMPILE_COMMAND, file_path);

    // Compile kata file
    if (system(compile_command) != 0) {
        strncpy(result_buffer.str, "Compilation error", result_buffer.len);
        return KATA_COMPILATION_FAILURE;
    }

    // Run compiled kata file
    FILE *fp = popen(RUN_COMMAND, "r");
    if (fp == NULL) {
        strncpy(result_buffer.str, "Execution error", result_buffer.len);
        return KATA_EXECUTION_FAILURE;
    }

    // Read output to result_buffer
    fgets(result_buffer.str, (int)result_buffer.len, fp);
    int status = pclose(fp);

    // Check execution status
    if (status != 0) {
        strncpy(result_buffer.str, "Execution error", result_buffer.len);
        return KATA_EXECUTION_FAILURE;
    }

    return KATA_SUCCESS;
}
