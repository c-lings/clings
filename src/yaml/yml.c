
//
// Created by Theo OMNES on 16/11/2023.
//

#include "stdbool.h"
#include "yml.h"

Kata parse_kata(yaml_parser_t *parser, yaml_event_t *event);

void push_kata_in_list(Kata kata, KataList *list);

Kata no_kata();

KataListParsingResult parse_kata_list(char *file_path) {
    bool done = false;
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    FILE *input = fopen(file_path, "rb");
    if(input == NULL) {
        return (KataListParsingResult) {
                .success = false,
                .error_message = "Failed to open yaml file"
        };
    }

    yaml_parser_set_input_file(&parser, input);
    KataList kata_list = {
            .katas = NULL,
            .len = 0
    };
    while (true) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_delete(&parser);
            return (KataListParsingResult) {
                    .success = false,
                    .error_message = "Failed to parse file info.yml"
            };
        }
        if(event.type == YAML_STREAM_END_EVENT) break;
        if(event.type == YAML_SEQUENCE_START_EVENT) {
            while(event.type != YAML_STREAM_END_EVENT) {
                Kata kata = parse_kata(&parser, &event);
                if(event.type == YAML_SEQUENCE_END_EVENT) break;
                if(kata.name.len != 0 && kata.path.len != 0)
                    push_kata_in_list(kata, &kata_list);
                yaml_parser_parse(&parser, &event);
            }
        }
    }
    yaml_event_delete(&event);

    return (KataListParsingResult) {
            .success = true,
            .kata_list = kata_list
    };
}

void push_kata_in_list(Kata kata, KataList *list) {
    list->len++;
    list->katas = (Kata *) realloc(list->katas, list->len * sizeof(Kata));
    list->katas[list->len - 1] = kata;
}

Kata parse_kata(yaml_parser_t *parser, yaml_event_t *event) {
    yaml_parser_parse(parser, event);
    Kata kata = {.name = empty_sized_string(), .path = empty_sized_string()};
    if(event->type != YAML_MAPPING_START_EVENT) return no_kata();

    yaml_parser_parse(parser, event);
    if(event->type != YAML_SCALAR_EVENT || strcmp((char *)event->data.scalar.value, "name") != 0) return no_kata();

    yaml_parser_parse(parser, event);
    if(event->type != YAML_SCALAR_EVENT) return no_kata();
    kata.name = copy_str_to_sized_string((char *)event->data.scalar.value, event->data.scalar.length);

    yaml_parser_parse(parser, event);
    if(event->type != YAML_SCALAR_EVENT || strcmp((char *)event->data.scalar.value, "path") != 0) {
        free_sized_string(kata.name);
        return no_kata();
    }

    yaml_parser_parse(parser, event);
    if(event->type != YAML_SCALAR_EVENT) {
        free_sized_string(kata.name);
        return no_kata();
    }
    kata.path = copy_str_to_sized_string((char *)event->data.scalar.value, event->data.scalar.length);

    return kata;
}

Kata no_kata() {
    return (Kata) {
            .name = empty_sized_string(),
            .path = empty_sized_string()
    };
}
