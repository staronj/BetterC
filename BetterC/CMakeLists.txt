cmake_minimum_required (VERSION 2.8)
project (BetterC)

set(SOURCES better_string.c better_string.h string_builder.c string_builder.h input_stream.c input_stream.h vector.h vector.c safe_memory_operations.c safe_memory_operations.h safe_utility.c safe_utility.h err.c err.h algorithm.c algorithm.h)

add_library(BetterC ${SOURCES})
add_subdirectory(tests)