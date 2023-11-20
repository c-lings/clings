cmake_minimum_required(VERSION 3.26)
project(clings_yaml C)

find_package(yaml CONFIG REQUIRED)

add_library(clings_yaml
        yml.c
        yaml_parser_factory.c
)
target_link_libraries(clings_yaml PUBLIC yaml)


# TESTS
find_package(unofficial-cunit CONFIG REQUIRED)
find_package(cmocka CONFIG REQUIRED)
add_executable(tests_clings_yaml
        yaml_test.c
        ../types/sized_string.c
        ../katas/katas.c
)
target_link_libraries(tests_clings_yaml PRIVATE clings_yaml yaml unofficial::cunit::cunit)
add_test(NAME tests_clings_yaml COMMAND tests_clings_yaml)
