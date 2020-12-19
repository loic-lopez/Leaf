//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_CONFIG_FILE_NOT_FOUND_HPP
#define LEAF_CONFIG_FILE_NOT_FOUND_HPP

#include <string>
#include <utility>
#include <boost/exception/errinfo_file_name.hpp>
#include "exceptions/abstracts/exception.hpp"
#include "exceptions/error_info.hpp"

namespace Leaf::Exceptions::Abstracts {

    class ConfigFileNotFound : public Exception {
    protected:
        std::string _configFilePath;

        void buildStdExceptionMessage(const char *exceptionClassName, const char *fileName);

    public:
        explicit ConfigFileNotFound(
                std::string configFilePath,
                char const *atFunction,
                int atLine,
                int _errno
        );
    };
}

#endif //LEAF_CONFIG_FILE_NOT_FOUND_HPP
