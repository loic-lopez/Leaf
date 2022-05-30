//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_EXCEPTION_HPP
#define LEAF_EXCEPTION_HPP

#include <iostream>
#include <source_location>
#include <string>
#include <utility>

#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/errinfo_at_line.hpp>
#include <boost/exception/errinfo_errno.hpp>

#include "concept/leaf_concepts.hpp"
#include "interface/iexception.hpp"

namespace leaf::exception::abstract
{

class Exception : public interface::IException
{
  public:
    explicit Exception(const std::source_location &sourceLocation);
    virtual ~Exception() = default;

    const char *what() const noexcept override;

  protected:
    std::string _msg;
    virtual void buildStdExceptionMessage(const char *exceptionClassName) = 0;

  private:
    std::source_location _sourceLocation;
};

}// namespace leaf::exception::abstract

#endif// LEAF_EXCEPTION_HPP