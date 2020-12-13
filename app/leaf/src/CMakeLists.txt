set(LEAF_SOURCES

        # abstracts
        ${CMAKE_CURRENT_SOURCE_DIR}/abstracts/ini_configuration_loader.cpp


        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.cpp

        # server
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_process_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_server_options_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/models/leaf_server_options.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/configuration_loaders/leaf_server_configuration_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/configuration_loaders/leaf_mime_types_loader.cpp

        PARENT_SCOPE
        )