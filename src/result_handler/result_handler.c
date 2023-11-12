#include <stdio.h>
#include "result_handler.h"

void handle_kata_result(kata_status result_status, sized_string_t result_string) {
    switch (result_status) {
        case KATA_SUCCESS:
            printf("Success !");
            break;
        case KATA_COMPILATION_FAILURE:
            printf("Compilation failure...");
            break;
        case KATA_EXECUTION_FAILURE:
            printf("Execution failure...");
            break;
        case KATA_TEST_FAILURE:
            printf("Unit tests failure...");
            break;
        case KATA_ERROR:
            printf("Error");
            break;
    }

    printf("\n\n");

    if (result_string.str && result_string.len > 0) {
        printf("%s", result_string.str);
    }

    printf("\n");
}
