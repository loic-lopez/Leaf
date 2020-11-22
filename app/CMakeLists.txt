project(${CMAKE_PROJECT_NAME})

set(LEAF_PROJECT_BINARY ${PROJECT_NAME})
set(LEAF_PROJECT_LIBRARY ${PROJECT_NAME}_lib)
set(LEAF_PROJECT_TESTS ${PROJECT_NAME}_tests)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

# Include Leaf
add_subdirectory(leaf)

# Include Leaf tests
add_subdirectory(tests)