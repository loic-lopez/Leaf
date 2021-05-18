## Setup gtest
find_package(GTest REQUIRED)

include_directories(include)

set(GTEST_LIBS GTest::gmock_main GTest::gmock GTest::gtest)

add_executable(${LEAF_PROJECT_TESTS}
        src/leaf_server_mime_types_tests.cpp
        src/leaf_server_configuration_loader_tests.cpp
        src/leaf_server_options_parser_tests.cpp

        include/tests/leaf_server_options_parser_test.hpp
        include/tests/leaf_server_configuration_loader_test.hpp
        include/tests/leaf_server_mime_types_loader_test.hpp
        )

add_dependencies(${LEAF_PROJECT_TESTS} ${GTEST_LIBS})

target_link_libraries(${LEAF_PROJECT_TESTS}
        ${GTEST_LIBS}
        ${LEAF_ENABLED_BOOST_LIBRARIES}
        ${LEAF_PROJECT_LIBRARY}
        )

## Output dirs
set(LEAF_TEST_GENERATED_INCLUDE_ROOT_PATH ${CMAKE_BINARY_DIR}/include/tests)

configure_file(include/generated/leaf_tests_config.hpp.in ${LEAF_TEST_GENERATED_INCLUDE_ROOT_PATH}/generated/leaf_tests_config.hpp)

target_include_directories(${LEAF_PROJECT_TESTS} PUBLIC ${LEAF_TEST_GENERATED_INCLUDE_ROOT_PATH})

add_test(NAME ${LEAF_PROJECT_TESTS}
        COMMAND ${LEAF_PROJECT_TESTS} --gtest_output=xml:${CMAKE_BINARY_DIR}/test_reports/gtest/gtest_output.xml)



