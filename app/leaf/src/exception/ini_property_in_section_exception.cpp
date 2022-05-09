//
// Created by LoicL on 23/12/2020.
//

#include <utility>

#include <boost/format.hpp>

#include "exception/error_info.hpp"
#include "exception/ini_property_in_section_exception.hpp"

namespace leaf::exception
{

IniPropertyInSectionException::IniPropertyInSectionException(const ExceptionType exceptionType,
                                                             const std::string_view &property, const std::string_view &section,
                                                             const std::string_view &configFilePath, const std::source_location &location)
    : exception::IniSectionNotFound(section, configFilePath, location), _property(property), _exceptionType(exceptionType)
{
  IniPropertyInSectionException::buildStdExceptionMessage(__FUNCTION__);
  *this << exception::error_info::errinfo_ini_property_in_section(_property);
}

void IniPropertyInSectionException::buildStdExceptionMessage(const char *exceptionClassName)
{
  boost::format exceptionFormat("%1% exception raised:\nthis means the leaf_server ini config file located at %2% %3%.");
  exceptionFormat % exceptionClassName;
  exceptionFormat % _configFilePath;
  if (_exceptionType == ExceptionType::MISSING)
  {
    exceptionFormat % (" doesn't have a property " + _property + " in section " + _section + " while it is required.");
  }
  else
  {
    exceptionFormat % (" the property " + _property + " is declared multiple times in section " + _section);
  }

  _msg = exceptionFormat.str();
}

}// namespace leaf::exception