cmake_minimum_required (VERSION 2.8)
project (BetterC)

enable_testing()

if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            --build-config "$<CONFIGURATION>")
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/BetterC)

file(GLOB files "*_test.c")
foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${name}.c)
    target_link_libraries(${name} BetterC)
    add_test(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name})
endforeach()

