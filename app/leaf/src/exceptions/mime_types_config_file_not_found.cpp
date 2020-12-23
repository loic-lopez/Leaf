//
// Created by LoicL on 29/11/2020.
//

#include "exceptions/mime_types_config_file_not_found.hpp"


Leaf::Exceptions::MimeTypesConfigFileNotFound::MimeTypesConfigFileNotFound(const std::string &configFilePath,
                                                                           const char *atFunction, int atLine,
                                                                           int _errno) : ConfigFileNotFound(
        configFilePath, atFunction, atLine, _errno) {
    ConfigFileNotFound::buildStdExceptionMessage("MimeTypesConfigFileNotFound");
    *this << Exceptions::ErrorInfo::errinfo_mime_types_config_file_path(_configFilePath);
}
