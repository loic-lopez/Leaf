//
// Created by LoicL on 23/12/2020.
//

#include <utility>

#include "exception/error_info.hpp"
#include "exception/ini_section_not_found.hpp"

namespace leaf::exception
{

IniSectionNotFound::IniSectionNotFound(const std::string &section, const std::string &configFilePath, const std::source_location &location)
    : Exception(location), _section(section), _configFilePath(configFilePath)
{
  IniSectionNotFound::buildStdExceptionMessage("IniSectionNotFound");
  *this << exception::error_info::errinfo_ini_section(section);
}

void IniSectionNotFound::buildStdExceptionMessage(const char *exceptionClassName)
{
  _msg = exceptionClassName;
  _msg += " exception raised:\n";
  _msg += "this means the leaf_server ini config file located at " + _configFilePath + " doesn't have a section ";
  _msg += _section + " while it is required.";
}

}// namespace leaf::exception
