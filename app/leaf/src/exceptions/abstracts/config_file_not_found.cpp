//
// Created by LoicL on 12/12/2020.
//

#include "exceptions/abstracts/config_file_not_found.hpp"

void Leaf::Exceptions::Abstracts::ConfigFileNotFound::buildStdExceptionMessage(const char *exceptionClassName) {
    _msg = exceptionClassName;
    _msg += " exception raised:\n";
    _msg += "this means config file located at " + _configFilePath + " doesn't exists.";
}

Leaf::Exceptions::Abstracts::ConfigFileNotFound::ConfigFileNotFound(
        std::string configFilePath,
        int _errno,
        const boost::source_location &location
) : ExceptionWithErrno(location, _errno), _configFilePath(std::move(configFilePath)) {

}


