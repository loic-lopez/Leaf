//
// Created by LoicL on 29/11/2020.
//

#include "exceptions/leaf_server_config_file_not_found.hpp"

Leaf::Exceptions::LeafServerConfigFileNotFound::LeafServerConfigFileNotFound(const std::string &configFilePath,
                                                                             const char *atFunction, int atLine,
                                                                             int _errno) : ConfigFileNotFound(
        configFilePath, atFunction, atLine, _errno) {
    ConfigFileNotFound::buildStdExceptionMessage("LeafServerConfigFileNotFound");
    *this << Exceptions::ErrorInfo::errinfo_server_config_file_path(_configFilePath);
}
