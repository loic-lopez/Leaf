## Vars
project(LeafTests)

## Setup gtest
enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} cpp/app_test.cpp)
target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main app)
add_test(${PROJECT_NAME} ${PROJECT_NAME})





