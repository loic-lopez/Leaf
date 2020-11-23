project(${CMAKE_PROJECT_NAME})

string(TOLOWER ${PROJECT_NAME} LEAF_PROJECT)
message("Leaf: ${LEAF_PROJECT}")
set(LEAF_PROJECT_BINARY ${LEAF_PROJECT})
set(LEAF_PROJECT_LIBRARY ${LEAF_PROJECT}_lib)
set(LEAF_PROJECT_TESTS ${LEAF_PROJECT}_tests)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

# Find boost library
FIND_PACKAGE(Boost REQUIRED)
set(LEAF_ENABLED_BOOST_LIBRARIES Boost::Boost)

# Include Leaf
add_subdirectory(leaf)

# Include Leaf tests
add_subdirectory(tests)