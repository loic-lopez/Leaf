//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP
#define LEAF_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP

#include "exceptions/abstracts/config_file_not_found.hpp"

namespace Leaf::Exceptions {

    class MimeTypesConfigFileNotFound : public Exceptions::Abstracts::ConfigFileNotFound {

    public:
        explicit MimeTypesConfigFileNotFound(
                const std::string &configFilePath,
                char const *atFunction,
                int atLine,
                int _errno
        ) : ConfigFileNotFound(configFilePath, atFunction, atLine, _errno) {
            ConfigFileNotFound::buildStdExceptionMessage("MimeTypesConfigFileNotFound", "mime_types.ini");
            *this << Exceptions::ErrorInfo::errinfo_mime_types_config_file_path(_configFilePath);
        }
    };
}


#endif //LEAF_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP
