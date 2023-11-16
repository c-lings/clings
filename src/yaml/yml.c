
//
// Created by Theo OMNES on 16/11/2023.
//

#include "stdbool.h"
#include "yml.h"

YamlParsingResult parse_kata_list(char *file_path) {
    bool done = false;
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    FILE *input = fopen("info.yml", "rb");
    if(input == NULL) {
        return (YamlParsingResult) {
                .success = false,
                .error_message = "Failed to open file info.yml"
        };
    }



    yaml_parser_set_input_file(&parser, input);

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_delete(&parser);
            return (YamlParsingResult) {
                    .success = false,
                    .error_message = "Failed to parse file info.yml"
            };
        }

        // TODO

        done = (event.type == YAML_STREAM_END_EVENT);
        yaml_event_delete(&event);

    }

    return (YamlParsingResult) {
            .success = true,
            .kata_list = NULL
    };
}