#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "execution.h"

kata_status run_kata(const kata_t kata, sized_string_t result_buffer) {
    char compile_command[MAX_PATH_LENGTH];

    // check if file exists
    FILE* file = fopen(kata.path.str, "r");
    if(file == NULL) {
        strncpy(result_buffer.str, "File not found", result_buffer.len);
        return KATA_ERROR;
    }
    fclose(file);

    // Create compile command
    printf("Compiling %s\n", kata.path.str);
    snprintf(compile_command, MAX_PATH_LENGTH, COMPILE_COMMAND, kata.path.str);

    // Compile kata file
	FILE *cmd_fp = popen(compile_command, "r");
	if (cmd_fp == NULL)
	{
		fprintf(stderr, "[Error] Couldn't execute compile command");
		exit(EXIT_FAILURE);
	}


	char buffer[4096];
	while (fgets(buffer, 4096, cmd_fp) != NULL)
		printf("%s\n", buffer);

	int compile_status = pclose(cmd_fp);

    if (compile_status != 0) {
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
	switch (status)
	{
	case EXIT_FAILURE:
        strncpy(result_buffer.str, "Execution error", result_buffer.len);
        return KATA_EXECUTION_FAILURE;

	case EXIT_SUCCESS:
    	return KATA_SUCCESS;

	default:
		return KATA_ERROR;
	}
}
