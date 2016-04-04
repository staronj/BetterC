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

add_executable(algorithm_test algorithm_test.c)
target_link_libraries(algorithm_test BetterC ${CHECK_LIBRARIES})
add_test(algorithm_test ${CMAKE_CURRENT_BINARY_DIR}/algorithm_test)