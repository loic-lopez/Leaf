# Find boost library
find_package(Boost REQUIRED)
link_directories(${Boost_LIB_DIRS})

set(LEAF_ENABLED_BOOST_LIBRARIES Boost::Boost)

add_subdirectory(include)
add_subdirectory(src)

# Construct Leaf library
add_library(${LEAF_PROJECT_LIBRARY} ${LEAF_INCLUDES} ${LEAF_SOURCES})
target_link_libraries(${LEAF_PROJECT_LIBRARY} PRIVATE ${LEAF_ENABLED_BOOST_LIBRARIES})

# Construct Leaf executable binary
add_executable(
        ${LEAF_PROJECT_BINARY}
        src/main.cpp
)
target_link_libraries(${LEAF_PROJECT_BINARY} ${LEAF_PROJECT_LIBRARY})