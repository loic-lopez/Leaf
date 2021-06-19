string(TOLOWER ${CMAKE_PROJECT_NAME} LEAF_PROJECT)

string(TIMESTAMP BUILD_DATE "%Y/%m/%d")
set(LEAF_PROJECT_BINARY ${LEAF_PROJECT})
set(LEAF_PROJECT_LIBRARY ${LEAF_PROJECT}_lib)
set(LEAF_PROJECT_TESTS ${LEAF_PROJECT}_tests)

# Find boost library
find_package(Boost EXACT COMPONENTS program_options filesystem thread REQUIRED)

set(LEAF_ENABLED_BOOST_LIBRARIES Boost::program_options Boost::thread Boost::filesystem)

option(LEAF_CODE_COVERAGE "LEAF_CODE_COVERAGE" OFF)

if (NOT MSVC AND LEAF_CODE_COVERAGE)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage -fno-inline")
    if (APPLE)
        SET(GCC_COVERAGE_LINK_FLAGS "-coverage")
    else ()
        SET(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
    endif ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
endif ()


# Include Leaf
add_subdirectory(leaf)

# Include Leaf tests
add_subdirectory(tests)