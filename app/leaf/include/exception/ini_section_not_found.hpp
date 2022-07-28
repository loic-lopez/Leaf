//
// Created by LoicL on 23/12/2020.
//

#ifndef __LEAF_ABSTRACT_INI_SECTION_NOT_FOUND_HPP__
#define __LEAF_ABSTRACT_INI_SECTION_NOT_FOUND_HPP__

#include "defines/leaf_defines.hpp"
#include "exception/abstract/exception.hpp"

#include <filesystem>

namespace leaf::exception
{
class IniSectionNotFound : public exception::abstract::Exception
{
  public:
    explicit IniSectionNotFound(const defines::ini::Section &section, defines::Path configFilePath, const std::source_location &location);

  protected:
    std::string _section;
    defines::Path _configFilePath;

    void buildStdExceptionMessage(const char *exceptionClassName) override;
};
}// namespace leaf::exception

#endif// __LEAF_ABSTRACT_INI_SECTION_NOT_FOUND_HPP__
