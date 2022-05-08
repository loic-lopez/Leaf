//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_EXCEPTION_WITH_ERRNO_HPP
#define LEAF_EXCEPTION_WITH_ERRNO_HPP

#include "exception/abstract/exception.hpp"

namespace leaf::exception::abstract
{

class ExceptionWithErrno : public Exception
{
 protected:
  int _errno;

 public:
  explicit ExceptionWithErrno(const std::source_location &sourceLocation, int _errno);
};
}// namespace leaf::exception::abstract

#endif// LEAF_EXCEPTION_WITH_ERRNO_HPP
