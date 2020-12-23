//
// Created by LoicL on 23/12/2020.
//

#include <utility>
#include "exceptions/ini_section_not_found.hpp"

Leaf::Exceptions::IniSectionNotFound::IniSectionNotFound(std::string section,
                                                         std::string configFilePath, const char *atFunction, int atLine)
        : Exception(atFunction, atLine),
          _section(std::move(section)),
          _configFilePath(std::move(configFilePath)) {
}

void Leaf::Exceptions::IniSectionNotFound::buildStdExceptionMessage(const char *exceptionClassName) {
    _msg = exceptionClassName;
    _msg += " exception raised: this means the";
    _msg += " server ini config file located at " + _configFilePath + " doesn't have a section ";
    _msg += _section + " while it is required. ";
}
