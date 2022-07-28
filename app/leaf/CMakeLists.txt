add_subdirectory(include)
add_subdirectory(src)

## Output dirs
set(LEAF_GENERATED_INCLUDE_ROOT_PATH ${CMAKE_BINARY_DIR}/include)

## Dirs in projects
set(PROJECT_INCLUDE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

## Create output dirs
file(MAKE_DIRECTORY ${LEAF_GENERATED_INCLUDE_ROOT_PATH})

## Generated Headers
configure_file(${PROJECT_INCLUDE_ROOT_PATH}/utils/leaf_build.hpp.in ${LEAF_GENERATED_INCLUDE_ROOT_PATH}/utils/leaf_build.hpp)

find_package(fmt REQUIRED)

set(SPDLOG_LIBS ${CONAN_PKG_LIBS_SPDLOG} fmt::fmt)

# Construct Leaf library
add_library(${LEAF_PROJECT_LIBRARY} ${LEAF_INCLUDES} ${LEAF_SOURCES})
target_link_libraries(${LEAF_PROJECT_LIBRARY} ${LEAF_ENABLED_BOOST_LIBRARIES} ${SPDLOG_LIBS})
target_include_directories(${LEAF_PROJECT_LIBRARY} PUBLIC ${LEAF_GENERATED_INCLUDE_ROOT_PATH})

# Construct Leaf executable binary
add_executable(
        ${LEAF_PROJECT_BINARY}
        src/main.cpp
)
target_link_libraries(${LEAF_PROJECT_BINARY} ${LEAF_PROJECT_LIBRARY})
