cmake_minimum_required(VERSION 3.27)
project(clings C)

set(CMAKE_C_STANDARD 11)

add_executable(clings main.c
        src/execution/execution.c
        src/types/sized_string.c
        src/result_handler/result_handler.c
        src/clings.c
        src/katas/katas.c)
