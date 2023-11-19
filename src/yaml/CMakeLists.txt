cmake_minimum_required(VERSION 3.26)
project(clings_yaml C)

find_package(yaml CONFIG REQUIRED)
find_package(cmocka CONFIG REQUIRED)

add_library(clings_yaml
        yml.c
        yaml_parser_factory.c
)
target_link_libraries(clings_yaml PUBLIC yaml)

add_executable(tests_clings_yaml yaml_test.c)
add_test(NAME tests_clings_yaml COMMAND tests_clings_yaml)
target_link_libraries(tests_clings_yaml PUBLIC cmocka::cmocka)