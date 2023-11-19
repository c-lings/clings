#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>



static void test_nothing(void **state) {
    (void) state; /* unused */
}

int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_nothing),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

