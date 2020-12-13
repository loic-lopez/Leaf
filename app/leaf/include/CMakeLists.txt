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

        # Exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/mime_types_config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/leaf_server_config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/error_info.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/config_file_not_found.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/abstracts/exception.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/http/http.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/https/https.hpp

        # Server
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_server.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_server_options_parser.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/models/leaf_server_options.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_process_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/configuration_loaders/leaf_server_configuration_loader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/configuration_loaders/leaf_mime_types_loader.hpp

        PARENT_SCOPE
        )