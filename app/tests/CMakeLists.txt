
## Setup gtest
enable_testing()
include(${CMAKE_BINARY_DIR}/GTestConfig.cmake)

add_executable(${LEAF_PROJECT_TESTS}
        cpp/app_test.cpp
        cpp/mime_types_tests.cpp
        cpp/leaf_conf_tests.cpp
        )

set(GTEST_LIBS GTest::gmock_main GTest::gmock GTest::gtest)

target_link_libraries(${LEAF_PROJECT_TESTS}
        ${GTEST_LIBS}
        ${LEAF_ENABLED_BOOST_LIBRARIES}
        ${LEAF_PROJECT_LIBRARY}
        )

add_test(${LEAF_PROJECT_TESTS} ${LEAF_PROJECT_TESTS})





