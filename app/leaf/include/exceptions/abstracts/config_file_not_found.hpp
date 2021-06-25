//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_CONFIG_FILE_NOT_FOUND_HPP
#define LEAF_CONFIG_FILE_NOT_FOUND_HPP

#include <string>
#include <utility>
#include <boost/exception/errinfo_file_name.hpp>
#include "exceptions/abstracts/exception_with_errno.hpp"
#include "exceptions/error_info.hpp"

namespace Leaf::Exceptions::Abstracts {

    class ConfigFileNotFound : public ExceptionWithErrno {
    protected:
        std::string _configFilePath;

        void buildStdExceptionMessage(const char *exceptionClassName) override;

    public:
        explicit ConfigFileNotFound(
                std::string configFilePath,
                int _errno,
                const std::source_location &location
        );
    };
}

#endif //LEAF_CONFIG_FILE_NOT_FOUND_HPP
