#include <printf.h>
#include "clings.h"
#include "types/types.h"
#include "execution/execution.h"
#include "result_handler/result_handler.h"
#include "katas/katas.h"
#include "yaml/yml.h"
#include "yaml/yaml_parser_factory.h"

int clings() {
    yaml_parser_t parser = parser_factory("info.yml");
    if(parser.error != YAML_NO_ERROR) {
        fprintf(stderr, "Failed to open yaml file: %s\n", parser.problem);
        return EXIT_FAILURE;
    }

    kata_list_parsing_result_t kata_list_parsing_result = parse_kata_list(parser);
    yaml_parser_delete(&parser);

    if (!kata_list_parsing_result.success) {
        fprintf(stderr, "Failed to parse kata list: %s\n", kata_list_parsing_result.error_message);
        return EXIT_FAILURE;
    }
    kata_list_t kata_list = kata_list_parsing_result.kata_list;

    bool no_kata = kata_list.len == 0;
    if (no_kata) return EXIT_SUCCESS;

    sized_string_t result_buffer = new_sized_string(256);

    for (int i = 0; i < kata_list.len; i++) {
        kata_status result = run_kata(kata_list.katas[i], result_buffer);
        handle_kata_result(result, result_buffer);

        if (result != KATA_SUCCESS) {
            break;
        } else {
            printf("====================\n\n");
        }
    }

    free_sized_string(&result_buffer);
    free_kata_list(&kata_list);

    return EXIT_SUCCESS;
}
