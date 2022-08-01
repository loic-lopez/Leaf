## Setup gtest
find_package(GTest REQUIRED)

include_directories(include)

set(GTEST_LIBS GTest::gmock_main GTest::gmock GTest::gtest)

add_executable(${LEAF_PROJECT_TESTS}
        src/leaf_server_mime_types_tests.cpp
        src/leaf_process_manager_configuration_loader_tests.cpp
        src/leaf_server_options_parser_tests.cpp
        src/leaf_server_tests.cpp
        src/leaf_server_configuration_loader_tests.cpp

        include/tests/leaf_server_options_parser_test.hpp
        include/tests/leaf_process_manager_configuration_loader_test.hpp
        include/tests/leaf_server_mime_types_loader_test.hpp
        )

add_dependencies(${LEAF_PROJECT_TESTS} ${GTEST_LIBS})

target_link_libraries(${LEAF_PROJECT_TESTS}
        ${GTEST_LIBS}
        ${LEAF_ENABLED_BOOST_LIBRARIES}
        ${LEAF_PROJECT_LIBRARY}
        )

add_test(NAME ${LEAF_PROJECT_TESTS}
        COMMAND ${LEAF_PROJECT_TESTS} --gtest_output=xml:${CMAKE_BINARY_DIR}/test_reports/gtest/gtest_output.xml)

## Dirs in projects
set(TESTS_CONFIG_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conf)
set(TESTS_SERVERS_ROOT_PATH ${TESTS_CONFIG_ROOT_PATH}/servers)
set(LEAF_TESTS_CONFIG_ROOT_PATH ${CMAKE_BINARY_DIR}/Testing/conf/)
set(LEAF_TEST_GENERATED_INCLUDE_ROOT_PATH ${CMAKE_BINARY_DIR}/include/tests)

## Create output dirs
file(MAKE_DIRECTORY ${LEAF_TESTS_CONFIG_ROOT_PATH}/servers)

## Server Config
configure_file(${TESTS_CONFIG_ROOT_PATH}/mime_types_empty.ini ${LEAF_TESTS_CONFIG_ROOT_PATH}/mime_types_empty.ini COPYONLY)
configure_file(${TESTS_CONFIG_ROOT_PATH}/leaf.template.with_missing_section.ini ${LEAF_TESTS_CONFIG_ROOT_PATH}/leaf.with_missing_section.ini)

## Leaf Servers
file(COPY ${TESTS_SERVERS_ROOT_PATH} DESTINATION ${LEAF_TESTS_CONFIG_ROOT_PATH})

configure_file(include/generated/leaf_tests_config.hpp.in ${LEAF_TEST_GENERATED_INCLUDE_ROOT_PATH}/generated/leaf_tests_config.hpp)

target_include_directories(${LEAF_PROJECT_TESTS} PUBLIC ${LEAF_TEST_GENERATED_INCLUDE_ROOT_PATH})


