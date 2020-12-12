set(LEAF_INCLUDES
        # Interfaces
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/iprotocol.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/iexception.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstracts/ini_configuration.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concepts/leaf_concepts.hpp

        # Library
        ${CMAKE_CURRENT_SOURCE_DIR}/library/singleton.hpp

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
        ${CMAKE_CURRENT_SOURCE_DIR}/server/leaf_conf.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server/mime_types.hpp

        PARENT_SCOPE
        )