## Setup gtest
enable_testing()

find_package(GTest REQUIRED)

include_directories(include)

add_executable(${LEAF_PROJECT_TESTS}
        src/leaf_server_mime_types_tests.cpp
        src/leaf_server_configuration_loader_tests.cpp
        src/leaf_server_options_parser_tests.cpp

        include/tests/leaf_server_options_parser_test.hpp
        include/tests/leaf_server_configuration_loader_test.hpp
        include/tests/leaf_server_mime_types_loader_test.hpp
        )

set(GTEST_LIBS GTest::gmock_main GTest::gmock GTest::gtest)

target_link_libraries(${LEAF_PROJECT_TESTS}
        ${GTEST_LIBS}
        ${LEAF_ENABLED_BOOST_LIBRARIES}
        ${LEAF_PROJECT_LIBRARY}
        )

add_test(${LEAF_PROJECT_TESTS} ${LEAF_PROJECT_TESTS})





