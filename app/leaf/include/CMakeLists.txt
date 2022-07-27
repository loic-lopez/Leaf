set(LEAF_INCLUDES
        # Interfaces
        ${CMAKE_CURRENT_SOURCE_DIR}/interface/iprotocol.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interface/iexception.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/ini_configuration_loader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concept/leaf_concepts.hpp

        # Library
        ${CMAKE_CURRENT_SOURCE_DIR}/library/singleton.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/library/constexpr_map.hpp

        # mime_type
        ${CMAKE_CURRENT_SOURCE_DIR}/mime_type/mime_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mime_type/mime_types.hpp


        ${CMAKE_CURRENT_SOURCE_DIR}/http/http_request.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/http_header.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/http_response.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/status_strings.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/stock_replies.hpp

        # Exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/mime_types_config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/leaf_server_config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/leaf_server_config_dir_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/leaf_exit_to_main.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/error_info.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/ini_section_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/ini_property_in_section_exception.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/abstract/config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/abstract/exception.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/abstract/exception_with_errno.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exception/abstract/exception_with_exit_status.hpp


        # Leaf Main Server (master process)
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_options_parser/leaf_options_parser.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager_options.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager_configuration.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loader/leaf_mime_types_loader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp

        # Leaf Server
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/leaf_server.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/connection_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/request_handler.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/leaf_server_configuration.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/configuration_loader/leaf_server_configuration_loader.hpp

        # Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.hpp

        PARENT_SCOPE
        )