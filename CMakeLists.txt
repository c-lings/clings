cmake_minimum_required(VERSION 3.26)
project(clings C)

set(CMAKE_C_STANDARD 11)

find_package(yaml CONFIG REQUIRED)

include_directories(src)

add_executable(clings main.c
        src/execution/execution.c
        src/execution/execution.h
        src/types/types.h
        src/types/sized_string.c
        src/result_handler/result_handler.c
        src/result_handler/result_handler.h
        src/clings.c
        src/katas/katas.c
        src/yaml/yml.c
)

file(COPY info.yml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY katas DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(clings PRIVATE yaml)