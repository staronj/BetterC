cmake_minimum_required (VERSION 2.8)
project (BetterC)

set(CMAKE_C_FLAGS "-D_SVID_SOURCE")
set(SOURCES system_headers.h thread.h thread.c mutex_and_signal.h mutex_and_signal.c message_queue.h message_queue.c)

add_library(BetterUnixC ${SOURCES})