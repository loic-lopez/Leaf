set(LEAF_INCLUDES
        # Interfaces
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/iprotocol.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/iexception.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstracts/ini_configuration_loader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concepts/leaf_concepts.hpp

        # Library
        ${CMAKE_CURRENT_SOURCE_DIR}/library/singleton.hpp

        # Models
        ${CMAKE_CURRENT_SOURCE_DIR}/models/mime_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/models/mime_types.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/models/http/http_request.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/models/http/http_header.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/models/http/http_response.hpp

        # Exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/mime_types_config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/leaf_server_config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/error_info.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/ini_section_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/ini_property_in_section_exception.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/exception.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/exception_with_errno.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/status_strings.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/http/stock_replies.hpp

        # Leaf Main Server (master process)
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_options_parser/leaf_options_parser.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/models/leaf_process_manager_options.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/models/leaf_process_manager_configuration.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loaders/leaf_mime_types_loader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/leaf_process_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.hpp

        # Leaf Server
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/leaf_server.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/connection_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/http/request_handler.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/models/leaf_server_configuration.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/leaf_server/configuration_loaders/leaf_server_configuration_loader.hpp

        # Streams
        ${CMAKE_CURRENT_SOURCE_DIR}/streams/synced_cout.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/streams/synced_cerr.hpp

        # Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.hpp

        PARENT_SCOPE
        )