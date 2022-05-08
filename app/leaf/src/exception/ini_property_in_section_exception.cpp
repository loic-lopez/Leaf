//
// Created by LoicL on 23/12/2020.
//

#include <utility>

#include "exception/error_info.hpp"
#include "exception/ini_property_in_section_exception.hpp"

namespace leaf::exception
{

IniPropertyInSectionException::IniPropertyInSectionException(const IniPropertyInSectionExceptionType exceptionType,
                                                             const std::string &property, const std::string &section,
                                                             const std::string &configFilePath, const std::source_location &location)
    : exception::IniSectionNotFound(section, configFilePath, location), _property(property), _exceptionType(exceptionType)
{
  IniPropertyInSectionException::buildStdExceptionMessage("IniPropertyInSectionNotFound");
  *this << exception::error_info::errinfo_ini_property_in_section(property);
}

void IniPropertyInSectionException::buildStdExceptionMessage(const char *exceptionClassName)
{
  _msg = exceptionClassName;
  _msg += " exception raised:\n";
  _msg += "this means the leaf_server ini config file located at " + _configFilePath;
  if (_exceptionType == IniPropertyInSectionExceptionType::MISSING)
  {
    _msg += " doesn't have a property ";
    _msg += _property + " in section ";
    _msg += _section + " while it is required.";
  }
  else { _msg += " the property " + _property + " is declared multiple times in section " + _section + "."; }
}

}// namespace leaf::exception