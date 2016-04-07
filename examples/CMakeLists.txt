cmake_minimum_required (VERSION 2.8)
project (BetterC)

file(GLOB files "*.c")
foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${name}.c)
    target_link_libraries(${name} BetterC BetterUnixC)
    add_test(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name})
endforeach()

configure_file(tcp_echo_run.sh ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tcp_echo_run.sh COPYONLY)
