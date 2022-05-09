//
// Created by LoicL on 29/11/2020.
//

#include "exception/leaf_server_config_file_not_found.hpp"

namespace leaf::exception
{

LeafServerConfigFileNotFound::LeafServerConfigFileNotFound(const std::string &configFilePath, int _errno,
                                                           const std::source_location &location)
    : ConfigFileNotFound(configFilePath, _errno, location)
{
  ConfigFileNotFound::buildStdExceptionMessage(__FUNCTION__);
  *this << exception::error_info::errinfo_server_config_file_path(_configFilePath);
}

}// namespace leaf::exception
