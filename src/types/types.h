#ifndef CLINGS_TYPES_H
#define CLINGS_TYPES_H

#include <stddef.h>
#include <stdlib.h>

typedef enum {
    KATA_SUCCESS, // the kata is done
    KATA_COMPILATION_FAILURE, // error at compile time
    KATA_EXECUTION_FAILURE, // error at run time
    KATA_TEST_FAILURE, // at least one unit test has failed
    KATA_ERROR // there was an error (file not found, etc.)
} kata_status;

typedef struct sized_string_t {
    char * str;
    size_t len;
} sized_string_t;

/**
 * @brief Creates a new sized_string_t with the specified length
 *
 * @param len The length of the string buffer to allocate
 * @return sized_string_t A sized_string_t with allocated string and specified length
 */
sized_string_t new_sized_string(size_t len);

sized_string_t copy_str_to_sized_string(char * str, size_t len);

sized_string_t empty_sized_string();

/**
 * @brief Frees the memory allocated for a sized_string_t
 *
 * @param string The sized_string_t to be freed
 */
void free_sized_string(sized_string_t *string);

#endif //CLINGS_TYPES_H
