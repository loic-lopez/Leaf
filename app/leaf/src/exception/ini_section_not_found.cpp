//
// Created by LoicL on 23/12/2020.
//

#include <utility>

#include <boost/format.hpp>

#include "exception/error_info.hpp"
#include "exception/ini_section_not_found.hpp"

namespace leaf::exception
{

IniSectionNotFound::IniSectionNotFound(const std::string_view &section, const std::string_view &configFilePath, const std::source_location &location)
    : Exception(location), _section(section), _configFilePath(configFilePath)
{
  IniSectionNotFound::buildStdExceptionMessage(__FUNCTION__);
  *this << exception::error_info::errinfo_ini_section(_section);
}

void IniSectionNotFound::buildStdExceptionMessage(const char *exceptionClassName)
{
  boost::format exceptionFormat("%1% exception raised:\nthis means the leaf_server ini config file located at %2% doesn't have a section %3% while it is required.");
  exceptionFormat % exceptionClassName % _configFilePath % _section;
  _msg = exceptionFormat.str();
}

}// namespace leaf::exception
