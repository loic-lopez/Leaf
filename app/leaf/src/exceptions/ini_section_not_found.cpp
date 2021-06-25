//
// Created by LoicL on 23/12/2020.
//

#include <utility>
#include "exceptions/error_info.hpp"
#include "exceptions/ini_section_not_found.hpp"

using namespace Leaf::Exceptions;

IniSectionNotFound::IniSectionNotFound(const std::string &section,
                                                         const std::string &configFilePath,
                                                         const std::source_location &location)
        : Exception(location),
          _section(section),
          _configFilePath(configFilePath) {
    IniSectionNotFound::buildStdExceptionMessage("IniSectionNotFound");
    *this << Exceptions::ErrorInfo::errinfo_ini_section(section);
}

void IniSectionNotFound::buildStdExceptionMessage(const char *exceptionClassName) {
    _msg = exceptionClassName;
    _msg += " exception raised:\n";
    _msg += "this means the leaf_server ini config file located at " + _configFilePath + " doesn't have a section ";
    _msg += _section + " while it is required.";
}
