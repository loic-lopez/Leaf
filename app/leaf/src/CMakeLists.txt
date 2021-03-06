set(LEAF_SOURCES

        # abstracts
        ${CMAKE_CURRENT_SOURCE_DIR}/abstracts/ini_configuration_loader.cpp

        # models
        ${CMAKE_CURRENT_SOURCE_DIR}/models/http/http_response.cpp

        # exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/mime_types_config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/leaf_server_config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/ini_section_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/exception_with_errno.cpp


        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.cpp

        # leaf_server
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/leaf_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/connection_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/request_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/models/leaf_server_configuration.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/configuration_loaders/leaf_server_configuration_loader.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_options_parser/leaf_options_parser.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/models/leaf_process_manager_options.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/models/leaf_process_manager_configuration.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loaders/leaf_mime_types_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.cpp

        PARENT_SCOPE
        )