cmake_minimum_required (VERSION 2.8)
project (BetterC)

set(CMAKE_C_FLAGS "-std=c99 -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_subdirectory(BetterC)
include_directories(BetterC)