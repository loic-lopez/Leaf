//
// Created by LoicL on 12/12/2020.
//

#include "exception/abstract/config_file_not_found.hpp"

namespace leaf::exception::abstract
{

void ConfigFileNotFound::buildStdExceptionMessage(const char *exceptionClassName)
{
  _msg = exceptionClassName;
  _msg += " exception raised:\n";
  _msg += "this means config file located at " + _configFilePath + " doesn't exists.";
}

ConfigFileNotFound::ConfigFileNotFound(std::string configFilePath, int _errno, const std::source_location &location)
    : ExceptionWithErrno(location, _errno), _configFilePath(std::move(configFilePath))
{
}

}// namespace leaf::exception::abstract
