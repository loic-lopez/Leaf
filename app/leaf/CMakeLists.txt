add_subdirectory(include)
add_subdirectory(src)

## Output dirs
set(LEAF_CONFIG_ROOT_PATH ${CMAKE_BINARY_DIR}/conf)
set(LEAF_SERVERS_ROOT_PATH ${LEAF_CONFIG_ROOT_PATH}/servers)
set(LEAF_GENERATED_INCLUDE_ROOT_PATH ${CMAKE_BINARY_DIR}/include)

## Dirs in projects
set(PROJECT_CONFIG_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conf)
set(PROJECT_SERVERS_ROOT_PATH ${PROJECT_CONFIG_ROOT_PATH}/servers)
set(PROJECT_INCLUDE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

## Create output dirs
file(MAKE_DIRECTORY ${LEAF_CONFIG_ROOT_PATH})
file(MAKE_DIRECTORY ${LEAF_SERVERS_ROOT_PATH})
file(MAKE_DIRECTORY ${LEAF_GENERATED_INCLUDE_ROOT_PATH})

## Generate dir for versioning
file(MAKE_DIRECTORY ${LEAF_GENERATED_INCLUDE_ROOT_PATH}/server)

## Generated Headers
configure_file(${PROJECT_INCLUDE_ROOT_PATH}/server/leaf_build.hpp.in ${LEAF_GENERATED_INCLUDE_ROOT_PATH}/server/leaf_build.hpp)

## Server Config
configure_file(${PROJECT_CONFIG_ROOT_PATH}/mime_types.ini ${LEAF_CONFIG_ROOT_PATH}/mime_types.ini COPYONLY)
configure_file(${PROJECT_CONFIG_ROOT_PATH}/leaf.template.ini ${LEAF_CONFIG_ROOT_PATH}/leaf.ini)

## Leaf Servers
configure_file(${PROJECT_SERVERS_ROOT_PATH}/http_port_80.ini ${LEAF_SERVERS_ROOT_PATH}/http_port_80.ini COPYONLY)

# Construct Leaf library
add_library(${LEAF_PROJECT_LIBRARY} ${LEAF_INCLUDES} ${LEAF_SOURCES})
target_link_libraries(${LEAF_PROJECT_LIBRARY} ${LEAF_ENABLED_BOOST_LIBRARIES})
target_include_directories(${LEAF_PROJECT_LIBRARY} PUBLIC ${LEAF_GENERATED_INCLUDE_ROOT_PATH})

# Construct Leaf executable binary
add_executable(
        ${LEAF_PROJECT_BINARY}
        main/main.cpp
)
target_link_libraries(${LEAF_PROJECT_BINARY} ${LEAF_PROJECT_LIBRARY})
