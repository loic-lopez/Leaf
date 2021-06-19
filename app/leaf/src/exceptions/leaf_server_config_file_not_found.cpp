//
// Created by LoicL on 29/11/2020.
//

#include "exceptions/leaf_server_config_file_not_found.hpp"

Leaf::Exceptions::LeafServerConfigFileNotFound::LeafServerConfigFileNotFound(
        const std::string &configFilePath,
        int _errno,
        const boost::source_location &location) : ConfigFileNotFound(configFilePath, _errno, location) {
    ConfigFileNotFound::buildStdExceptionMessage("LeafServerConfigFileNotFound");
    *this << Exceptions::ErrorInfo::errinfo_server_config_file_path(_configFilePath);
}
