cmake_minimum_required (VERSION 2.8)
project (BetterC)

set(CMAKE_C_FLAGS "-D_SVID_SOURCE")
set(SOURCES thread.h thread.c mutex_and_signal.h mutex_and_signal.c message_queue.h message_queue.c socket.h socket.c read_write_lock.c read_write_lock.h concurrent_queue.h concurrent_queue.c thread_pool.h thread_pool.c)

add_library(BetterUnixC ${SOURCES})
target_link_libraries (BetterUnixC BetterC)

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(PUBLIC BetterUnixC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(BetterUnixC "${CMAKE_THREAD_LIBS_INIT}")
endif()


