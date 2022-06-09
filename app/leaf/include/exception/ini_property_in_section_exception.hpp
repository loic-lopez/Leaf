//
// Created by LoicL on 23/12/2020.
//

#ifndef __LEAF_ABSTRACT_INI_PROPERTY_IN_SECTION_EXCEPTION_HPP__
#define __LEAF_ABSTRACT_INI_PROPERTY_IN_SECTION_EXCEPTION_HPP__

#include "exception/ini_section_not_found.hpp"

namespace leaf::exception
{
class IniPropertyInSectionException : public IniSectionNotFound
{
  public:
    enum class ExceptionType
    {
      DUPLICATED,
      MISSING
    };

    explicit IniPropertyInSectionException(
      ExceptionType exceptionType, const std::string_view &property, const std::string_view &section,
      const std::string_view &configFilePath, const std::source_location &location
    );

  protected:
    void buildStdExceptionMessage(const char *exceptionClassName) override;

  private:
    std::string _property;
    ExceptionType _exceptionType;
};

}// namespace leaf::exception

#endif// __LEAF_ABSTRACT_INI_PROPERTY_IN_SECTION_EXCEPTION_HPP__
