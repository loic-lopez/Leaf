set(LEAF_SOURCES

        # abstracts
        ${CMAKE_CURRENT_SOURCE_DIR}/abstracts/ini_configuration_loader.cpp

        # exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/mime_types_config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/leaf_server_config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/exception.cpp


        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.cpp

        # server
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_process_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_server_options_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/models/leaf_server_options.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/models/leaf_server_config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/configuration_loaders/leaf_server_configuration_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/configuration_loaders/leaf_mime_types_loader.cpp

        PARENT_SCOPE
        )