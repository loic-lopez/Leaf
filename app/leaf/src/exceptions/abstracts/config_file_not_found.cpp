//
// Created by LoicL on 12/12/2020.
//

#include "exceptions/abstracts/config_file_not_found.hpp"

void Leaf::Exceptions::Abstracts::ConfigFileNotFound::buildStdExceptionMessage(const char *exceptionClassName) {
    _msg = exceptionClassName;
    _msg += " exception raised: this means the";
    _msg += " config file located at " + _configFilePath + " doesn't exists.";
}

Leaf::Exceptions::Abstracts::ConfigFileNotFound::ConfigFileNotFound(
        std::string configFilePath,
        const char *atFunction,
        int atLine,
        int _errno
) : ExceptionWithErrno(atFunction, atLine, _errno), _configFilePath(std::move(configFilePath)) {

}


