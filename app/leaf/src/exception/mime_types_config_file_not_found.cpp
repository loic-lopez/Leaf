//
// Created by LoicL on 29/11/2020.
//

#include "defines/leaf_defines.hpp"
#include "exception/mime_types_config_file_not_found.hpp"

namespace leaf::exception
{

MimeTypesConfigFileNotFound::MimeTypesConfigFileNotFound(
  const defines::Path &configFilePath, const int errnoValue, const std::source_location &location
)
    : ConfigFileNotFound(configFilePath, errnoValue, location)
{
  ConfigFileNotFound::buildStdExceptionMessage(__FUNCTION__);
  *this << error_info::errinfo_mime_types_config_file_path(_configFilePath);
}

}// namespace leaf::exception