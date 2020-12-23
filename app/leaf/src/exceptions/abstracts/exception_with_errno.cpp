//
// Created by LoicL on 12/12/2020.
//

#include "exceptions/abstracts/exception_with_errno.hpp"

Leaf::Exceptions::Abstracts::ExceptionWithErrno::ExceptionWithErrno(const char *atFunction, int atLine, int _errno)
        : Exception(atFunction, atLine), _errno(_errno) {
    *this << boost::errinfo_errno(_errno);
}
