//
// Created by LoicL on 12/12/2020.
//

#include <boost/format.hpp>

#include "exception/abstract/config_file_not_found.hpp"

namespace leaf::exception::abstract
{

void ConfigFileNotFound::buildStdExceptionMessage(const char *exceptionClassName)
{
  boost::format exceptionFormat("%1% exception raised:\nthis means config file located at %2% doesn't exists.");
  exceptionFormat % exceptionClassName % _configFilePath;
  _msg = exceptionFormat.str();
}

ConfigFileNotFound::ConfigFileNotFound(std::string configFilePath, int _errno, const std::source_location &location)
    : ExceptionWithErrno(location, _errno), _configFilePath(std::move(configFilePath))
{
}

}// namespace leaf::exception::abstract
