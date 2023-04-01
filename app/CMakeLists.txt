string(TOLOWER ${CMAKE_PROJECT_NAME} LEAF_PROJECT)

string(TIMESTAMP BUILD_DATE "%Y/%m/%d")
set(LEAF_PROJECT_BINARY ${LEAF_PROJECT})
set(LEAF_PROJECT_LIBRARY ${LEAF_PROJECT}_lib)
set(LEAF_PROJECT_TESTS ${LEAF_PROJECT}_tests)

set(LEAF_ENABLED_BOOST_LIBRARIES Boost::program_options Boost::filesystem)

# Find boost library
find_package(boost COMPONENTS program_options filesystem REQUIRED)

option(LEAF_CODE_COVERAGE "LEAF_CODE_COVERAGE" OFF)

if (NOT MSVC AND LEAF_CODE_COVERAGE)
    set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage -fno-inline")
    if (APPLE)
        set(GCC_COVERAGE_LINK_FLAGS "-coverage")
    else ()
        set(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov -fno-inline")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
endif ()


# Include Leaf
add_subdirectory(leaf)

# Include Leaf tests
add_subdirectory(tests)