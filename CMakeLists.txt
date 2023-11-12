cmake_minimum_required(VERSION 3.27)
project(clings C)

set(CMAKE_C_STANDARD 11)

add_executable(clings main.c
        src/katas.h
        src/execution/execution.c
        src/execution/execution.h
        src/types/types.h
        src/types/sized_string.c
        src/result_handler/result_handler.c
        src/result_handler/result_handler.h
        src/clings.c
        src/clings.h
        src/katas/katas.c
        src/katas/katas.h)
