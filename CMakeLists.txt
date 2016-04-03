cmake_minimum_required (VERSION 2.8)
project (BetterC)

set(CMAKE_C_FLAGS "-std=c99 -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

include_directories(BetterC)
include_directories(BetterUnixC)
add_subdirectory(BetterC)
add_subdirectory(BetterUnixC)