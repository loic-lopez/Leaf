## Vars
project(LeafTests)

## Setup gtest
enable_testing()
include(${CMAKE_BINARY_DIR}/GTestConfig.cmake)

add_executable(${PROJECT_NAME} cpp/app_test.cpp)

set(GTEST_LIBS GTest::gmock_main GTest::gmock GTest::gtest)

target_link_libraries(${PROJECT_NAME}
        ${GTEST_LIBS}
        ${LEAF_PROJECT_LIBRARY}
        )

add_test(${PROJECT_NAME} ${PROJECT_NAME})





