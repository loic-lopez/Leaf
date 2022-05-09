set(LEAF_SOURCES

        # HTTP
        ${CMAKE_CURRENT_SOURCE_DIR}/http/http_response.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.cpp

        # exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/mime_types_config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/leaf_server_config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/leaf_server_config_dir_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/ini_section_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/ini_property_in_section_exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/abstract/config_file_not_found.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/abstract/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/abstract/exception_with_errno.cpp


        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.cpp

        # leaf_server
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/leaf_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/connection_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/request_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/leaf_server_configuration.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/configuration_loader/leaf_server_configuration_loader.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_options_parser/leaf_options_parser.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager_options.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager_configuration.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loader/leaf_mime_types_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.cpp

        PARENT_SCOPE
        )