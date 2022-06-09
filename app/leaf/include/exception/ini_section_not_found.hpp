//
// Created by LoicL on 23/12/2020.
//

#ifndef __LEAF_ABSTRACT_INI_SECTION_NOT_FOUND_HPP__
#define __LEAF_ABSTRACT_INI_SECTION_NOT_FOUND_HPP__

#include "exception/abstract/exception.hpp"

namespace leaf::exception
{
class IniSectionNotFound : public exception::abstract::Exception
{
  public:
    explicit IniSectionNotFound(
      const std::string_view &section, const std::string_view &configFilePath, const std::source_location &location
    );

  protected:
    std::string _section;
    std::string _configFilePath;

    void buildStdExceptionMessage(const char *exceptionClassName) override;
};
}// namespace leaf::exception

#endif// __LEAF_ABSTRACT_INI_SECTION_NOT_FOUND_HPP__
