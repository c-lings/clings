#include <printf.h>
#include "clings.h"
#include "types/types.h"
#include "execution/execution.h"
#include "result_handler/result_handler.h"
#include "katas/katas.h"

int clings() {
    sized_string_t result_buffer = new_sized_string(256);

    for (int i = 0; i < nb_kata_files; i++) {
        kata_status result = run_kata(i, result_buffer);
        handle_kata_result(result, result_buffer);

        if (result != KATA_SUCCESS) {
            break;
        } else {
            printf("====================\n\n");
        }
    }

    free_sized_string(result_buffer);

    return EXIT_SUCCESS;
}
