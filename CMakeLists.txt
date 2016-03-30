set(CMAKE_C_FLAGS "-std=c99 -Wall -g")

set(SOURCES better_string.c better_string.h string_builder.c string_builder.h input_stream.c input_stream.h vector.h vector.c safe_memory_operations.c safe_memory_operations.h safe_utility.c safe_utility.h)

add_library(lib ${SOURCES})