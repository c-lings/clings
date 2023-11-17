
//
// Created by Theo OMNES on 16/11/2023.
//

#include "stdbool.h"
#include "yml.h"

typedef struct KeyValueParsed KeyValueParsed;
struct KeyValueParsed {
    sized_string_t key;
    sized_string_t value;
};

KeyValueParsed parse_key_value(yaml_parser_t *parser, yaml_event_t *event);

Kata parse_kata(yaml_parser_t *parser, yaml_event_t *event);

KataListParsingResult kata_list_parsing_error();

void free_key_value_parsed(KeyValueParsed *key_value_parsed);

/**
 * @brief Parse the next event from the parser and store it in the event pointer.
 * If the parsing failed, the parser and the event are deleted.
 */
bool yaml_parse_next(yaml_parser_t *parser, yaml_event_t *event);

KataListParsingResult parse_kata_list(char *file_path) {
    FILE *input = fopen(file_path, "rb");
    if(input == NULL) {
        return (KataListParsingResult) {
                .success = false,
                .error_message = "Failed to open yaml file."
        };
    }

    yaml_parser_t parser;
    yaml_event_t event;
    yaml_parser_initialize(&parser);

    yaml_parser_set_input_file(&parser, input);
    KataList kata_list = {.katas = NULL, .len = 0};
    while (true) {
        if (!yaml_parse_next(&parser, &event)) return kata_list_parsing_error();
        if(event.type == YAML_STREAM_END_EVENT) break;

        if(event.type == YAML_SEQUENCE_START_EVENT) {
            while(event.type != YAML_STREAM_END_EVENT && event.type != YAML_SEQUENCE_END_EVENT) {
                Kata kata = parse_kata(&parser, &event);
                if(kata.name.len != 0 && kata.path.len != 0)
                    push_kata_in_list(kata, &kata_list);
            }
        }
    }

    yaml_parser_delete(&parser);
    yaml_event_delete(&event);
    return (KataListParsingResult) {
            .success = true,
            .kata_list = kata_list
    };
}

bool yaml_parse_next(yaml_parser_t *parser, yaml_event_t *event) {
    bool success = yaml_parser_parse(parser, event);
    if (!success) {
        yaml_parser_delete(parser);
        yaml_event_delete(event);
    }
    return success;
}

KataListParsingResult kata_list_parsing_error() {
    return (KataListParsingResult) {
            .success = false,
            .error_message = "Failed to parse file info.yml"
    };
}

Kata parse_kata(yaml_parser_t *parser, yaml_event_t *event) {
    Kata kata = no_kata();
    if (!yaml_parse_next(parser, event) || event->type != YAML_MAPPING_START_EVENT) return no_kata();

    KeyValueParsed name = parse_key_value(parser, event);
    if(!name.key.str || strcmp(name.key.str, "name") != 0) {
        free_key_value_parsed(&name);
        return no_kata();
    }
    kata.name = name.value;

    KeyValueParsed path = parse_key_value(parser, event);
    if(!path.key.str || strcmp(path.key.str, "path") != 0) {
        free_key_value_parsed(&name);
        free_key_value_parsed(&path);
        return no_kata();
    }
    kata.path = path.value;

    if(!yaml_parse_next(parser, event) || event->type != YAML_MAPPING_END_EVENT) {
        free_key_value_parsed(&name);
        free_key_value_parsed(&path);
        return no_kata();
    }

    free_sized_string(&name.key);
    free_sized_string(&path.key);
    return kata;
}

KeyValueParsed parse_key_value(yaml_parser_t *parser, yaml_event_t *event) {
    KeyValueParsed not_parsed = {.key = empty_sized_string(), .value = empty_sized_string()};

    // key
    if(!yaml_parser_parse(parser, event) || event->type != YAML_SCALAR_EVENT) return not_parsed;
    sized_string_t key = copy_str_to_sized_string((char *)event->data.scalar.value, event->data.scalar.length);

    // value
    if(!yaml_parser_parse(parser, event) || event->type != YAML_SCALAR_EVENT) {
        free_sized_string(&key);
        return not_parsed;
    }
    sized_string_t value = copy_str_to_sized_string((char *)event->data.scalar.value, event->data.scalar.length);


    if(key.len == 0 || value.len == 0) {
        free_sized_string(&key);
        free_sized_string(&value);
        return not_parsed;
    }
    return (KeyValueParsed) {.key = key, .value = value};
}

void free_key_value_parsed(KeyValueParsed *key_value_parsed) {
    free_sized_string(&key_value_parsed->key);
    free_sized_string(&key_value_parsed->value);
}