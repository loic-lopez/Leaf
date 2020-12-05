set(LEAF_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/abstracts/ini_configuration.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_conf.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/mime_types.cpp

        PARENT_SCOPE
        )