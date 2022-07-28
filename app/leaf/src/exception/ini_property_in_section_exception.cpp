//
// Created by LoicL on 23/12/2020.
//

#include "exception/error_info.hpp"
#include "exception/ini_property_in_section_exception.hpp"

#include <boost/format.hpp>

#include <utility>

namespace leaf::exception
{

IniPropertyInSectionException::IniPropertyInSectionException(
  const ExceptionType exceptionType, const std::string_view &property, const defines::ini::Section &section, const defines::Path &configFilePath,
  const std::source_location &location
)
    : IniSectionNotFound(section, configFilePath, location), _property(property), _exceptionType(exceptionType)
{
  IniPropertyInSectionException::buildStdExceptionMessage(__FUNCTION__);
  *this << error_info::errinfo_ini_property_in_section(_property);
}

void IniPropertyInSectionException::buildStdExceptionMessage(const char *exceptionClassName)
{
  boost::format exceptionFormat("%1% exception raised:\nthis means the ini config file located at %2% %3%.");
  exceptionFormat % exceptionClassName;
  exceptionFormat % _configFilePath;

  boost::format sectionNameFormat(boost::format("[%1%]") % _section);
  boost::format explanationExceptionFormat;

  if (_exceptionType == ExceptionType::MISSING)
  {
    explanationExceptionFormat =
      boost::format("doesn't have a property %1% in section %2% while it is required") % _property % sectionNameFormat;
  }
  else if (_exceptionType == ExceptionType::VALUE_MISSING_OR_INVALID)
  {
    explanationExceptionFormat = boost::format("in section %1% value of property %2% is empty or invalid") % sectionNameFormat % _property;
  }
  else
  {
    explanationExceptionFormat =
      boost::format("the property %1% is declared multiple times in section %2%") % _property % sectionNameFormat;
  }

  exceptionFormat % explanationExceptionFormat;

  _msg = exceptionFormat.str();
}

}// namespace leaf::exception