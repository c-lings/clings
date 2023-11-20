
#include "CUnit/Basic.h"
#include "yaml_parser_factory.h"

#define UNUSED(x) (void)(x)

static FILE* temp_file = NULL;
static char* file_path = "temp.yml";

int init(void) {
    if (NULL == (temp_file = fopen(file_path, "w+")))
        return -1;
    else
        return 0;
}

int clean(void) {
    if (0 != fclose(temp_file)) {
        return -1;
    }
    else {
        temp_file = NULL;
        return 0;
    }
}

void test_parser_factory(void) {
    yaml_parser_t parser = parser_factory(file_path);
    CU_ASSERT(parser.error == YAML_NO_ERROR);
    yaml_parser_delete(&parser);
}

void test_parser_factory_with_bad_path(void) {
    yaml_parser_t parser = parser_factory("bad/path/file.yml");
    CU_ASSERT(parser.error == YAML_READER_ERROR);
    CU_ASSERT_STRING_EQUAL(parser.problem, "Failed to open yaml file");
    yaml_parser_delete(&parser);
}

int main(void) {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Yaml", init, clean);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(pSuite, "given file exists", test_parser_factory);
    CU_add_test(pSuite, "given file does not exist", test_parser_factory_with_bad_path);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_number_of_tests_run() == 0;
}
