//
// Created by LoicL on 23/12/2020.
//

#include "exception/error_info.hpp"
#include "exception/ini_section_not_found.hpp"

#include <boost/format.hpp>

#include <utility>

namespace leaf::exception
{

IniSectionNotFound::IniSectionNotFound(const defines::ini::Section &section, defines::Path configFilePath, const std::source_location &location)
    : Exception(location), _section(section), _configFilePath(std::move(configFilePath))
{
  IniSectionNotFound::buildStdExceptionMessage(__FUNCTION__);
  *this << error_info::errinfo_ini_section(_section);
}

void IniSectionNotFound::buildStdExceptionMessage(const char *exceptionClassName)
{
  boost::format exceptionFormat(
    "%1% exception raised:\nthis means the leaf_server ini config file located at %2% doesn't have a section %3% while it is required."
  );
  exceptionFormat % exceptionClassName % _configFilePath % _section;
  _msg = exceptionFormat.str();
}

}// namespace leaf::exception
