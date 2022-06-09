//
// Created by LoicL on 12/12/2020.
//

#include "exception/abstract/exception_with_errno.hpp"

namespace leaf::exception::abstract
{

ExceptionWithErrno::ExceptionWithErrno(const std::source_location &sourceLocation, const int errnoValue)
    : Exception(sourceLocation), _errno(errnoValue)
{
  *this << boost::errinfo_errno(this->_errno);
}

}// namespace leaf::exception::abstract
