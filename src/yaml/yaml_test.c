
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>


#include "yaml_parser_factory.h"

#define UNUSED(x) (void)(x)


FILE *__wrap_fopen(const char * filename, const char * modes) {

    return mock_ptr_type(FILE*);
}


static void test_mock(void **state) {
    UNUSED(state);

    yaml_parser_t p = parser_factory("test.yaml");
    assert_int_equal(p.error, YAML_READER_ERROR);
}

int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_mock),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

