//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP
#define LEAF_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP

#include "exception/abstract/config_file_not_found.hpp"

namespace leaf::exception
{

class MimeTypesConfigFileNotFound : public exception::abstract::ConfigFileNotFound
{
  public:
    explicit MimeTypesConfigFileNotFound(const std::string &configFilePath, int _errno, const std::source_location &location);
};
}// namespace leaf::exception

#endif// LEAF_MIME_TYPES_CONFIG_FILE_NOT_FOUND_HPP
