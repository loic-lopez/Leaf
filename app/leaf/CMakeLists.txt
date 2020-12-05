add_subdirectory(include)
add_subdirectory(src)

# Construct Leaf library
add_library(${LEAF_PROJECT_LIBRARY} ${LEAF_INCLUDES} ${LEAF_SOURCES})
target_link_libraries(${LEAF_PROJECT_LIBRARY} ${LEAF_ENABLED_BOOST_LIBRARIES})

# Construct Leaf executable binary
add_executable(
        ${LEAF_PROJECT_BINARY}
        main/main.cpp
)
target_link_libraries(${LEAF_PROJECT_BINARY} ${LEAF_PROJECT_LIBRARY})

## CONF files
set(LEAF_CONFIG_ROOT_PATH ${CMAKE_BINARY_DIR}/conf)
set(LEAF_SERVERS_ROOT_PATH ${LEAF_CONFIG_ROOT_PATH}/servers)
set(PROJECT_CONFIG_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conf)
set(PROJECT_SERVERS_ROOT_PATH ${PROJECT_CONFIG_ROOT_PATH}/servers)

## Create output dirs
file(MAKE_DIRECTORY ${LEAF_CONFIG_ROOT_PATH})
file(MAKE_DIRECTORY ${LEAF_SERVERS_ROOT_PATH})

## Root Config
configure_file(${PROJECT_CONFIG_ROOT_PATH}/mime_types.ini ${LEAF_CONFIG_ROOT_PATH}/mime_types.ini COPYONLY)
configure_file(${PROJECT_CONFIG_ROOT_PATH}/leaf.template.ini ${LEAF_CONFIG_ROOT_PATH}/leaf.ini)

## Leaf Servers
configure_file(${PROJECT_SERVERS_ROOT_PATH}/http_port_80.ini ${LEAF_SERVERS_ROOT_PATH}/http_port_80.ini COPYONLY)
