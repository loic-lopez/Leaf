//
// Created by LoicL on 12/12/2020.
//

#ifndef __LEAF_ABSTRACT_EXCEPTION_WITH_ERRNO_HPP__
#define __LEAF_ABSTRACT_EXCEPTION_WITH_ERRNO_HPP__

#include "exception/abstract/exception.hpp"

namespace leaf::exception::abstract
{

class ExceptionWithErrno : public Exception
{
  public:
    explicit ExceptionWithErrno(const std::source_location &sourceLocation, int errnoValue);

  protected:
    int _errno;
};

}// namespace leaf::exception::abstract

#endif// __LEAF_ABSTRACT_EXCEPTION_WITH_ERRNO_HPP__
