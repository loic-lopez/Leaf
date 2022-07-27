//
// Created by LoicL on 12/12/2020.
//

#ifndef __LEAF_ABSTRACT_CONFIG_FILE_NOT_FOUND_HPP__
#define __LEAF_ABSTRACT_CONFIG_FILE_NOT_FOUND_HPP__

#include "exception/abstract/exception_with_errno.hpp"
#include "exception/error_info.hpp"

#include <boost/exception/errinfo_file_name.hpp>

#include <string>
#include <utility>

namespace leaf::exception::abstract
{

class ConfigFileNotFound : public ExceptionWithErrno
{
  public:
    explicit ConfigFileNotFound(std::string configFilePath, int errnoValue, const std::source_location &location);

  protected:
    std::string _configFilePath;

    void buildStdExceptionMessage(const char *exceptionClassName) override;
};

}// namespace leaf::exception::abstract

#endif// __LEAF_ABSTRACT_CONFIG_FILE_NOT_FOUND_HPP__
