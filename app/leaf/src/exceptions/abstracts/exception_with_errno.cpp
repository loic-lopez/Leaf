//
// Created by LoicL on 12/12/2020.
//

#include "exceptions/abstracts/exception_with_errno.hpp"

Leaf::Exceptions::Abstracts::ExceptionWithErrno::ExceptionWithErrno(const boost::source_location &sourceLocation, int _errno)
        : Exception(sourceLocation), _errno(_errno) {
    *this << boost::errinfo_errno(this->_errno);
}
