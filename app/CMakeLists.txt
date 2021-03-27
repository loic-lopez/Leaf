string(TOLOWER ${CMAKE_PROJECT_NAME} LEAF_PROJECT)

string(TIMESTAMP BUILD_DATE "%Y/%m/%d")
set(LEAF_PROJECT_BINARY ${LEAF_PROJECT})
set(LEAF_PROJECT_LIBRARY ${LEAF_PROJECT}_lib)
set(LEAF_PROJECT_TESTS ${LEAF_PROJECT}_tests)

# Find boost library
find_package(Boost EXACT COMPONENTS program_options filesystem thread REQUIRED)

set(LEAF_ENABLED_BOOST_LIBRARIES Boost::program_options Boost::thread Boost::filesystem)

# Include Leaf
add_subdirectory(leaf)

# Include Leaf tests
add_subdirectory(tests)