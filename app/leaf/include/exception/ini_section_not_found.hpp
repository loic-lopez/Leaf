//
// Created by LoicL on 23/12/2020.
//

#ifndef LEAF_INI_SECTION_NOT_FOUND_HPP
#define LEAF_INI_SECTION_NOT_FOUND_HPP

#include "exception/abstract/exception.hpp"

namespace leaf::exception
{
class IniSectionNotFound : public exception::abstract::Exception
{
 protected:
  std::string _section;
  std::string _configFilePath;

 public:
  explicit IniSectionNotFound(const std::string &section, const std::string &configFilePath, const std::source_location &location);

 protected:
  void buildStdExceptionMessage(const char *exceptionClassName) override;
};
}// namespace leaf::exception

#endif// LEAF_INI_SECTION_NOT_FOUND_HPP
