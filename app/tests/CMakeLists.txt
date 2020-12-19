
## Setup gtest
enable_testing()
include(${CMAKE_BINARY_DIR}/GTestConfig.cmake)

include_directories(include)

add_executable(${LEAF_PROJECT_TESTS}
        src/leaf_server_mime_types_tests.cpp
        src/leaf_server_ini_conf_tests.cpp
        src/leaf_server_options_parser_tests.cpp

        include/tests/leaf_server_options_parser_test.hpp
        )

set(GTEST_LIBS GTest::gmock_main GTest::gmock GTest::gtest)

target_link_libraries(${LEAF_PROJECT_TESTS}
        ${GTEST_LIBS}
        ${LEAF_ENABLED_BOOST_LIBRARIES}
        ${LEAF_PROJECT_LIBRARY}
        )

add_test(${LEAF_PROJECT_TESTS} ${LEAF_PROJECT_TESTS})





