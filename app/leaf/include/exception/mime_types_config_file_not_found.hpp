//
// Created by LoicL on 29/11/2020.
//

#ifndef __LEAF_ABSTRACT_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP__
#define __LEAF_ABSTRACT_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP__

#include "defines/leaf_defines.hpp"
#include "exception/abstract/config_file_not_found.hpp"

namespace leaf::exception
{

class MimeTypesConfigFileNotFound : public exception::abstract::ConfigFileNotFound
{
  public:
    explicit MimeTypesConfigFileNotFound(const defines::Path &configFilePath, int errnoValue, const std::source_location &location);
};
}// namespace leaf::exception

#endif// __LEAF_ABSTRACT_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP__
