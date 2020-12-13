//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_EXCEPTION_WITH_ERRNO_HPP
#define LEAF_EXCEPTION_WITH_ERRNO_HPP

#include "exceptions/abstracts/exception.hpp"

namespace Leaf::Exceptions::Abstracts {

    class ExceptionWithErrno : public Exception {
    protected:
        int _errno;
    public:
        explicit ExceptionWithErrno(const char *atFunction, int atLine, int _errno);
    };
}

#endif //LEAF_EXCEPTION_WITH_ERRNO_HPP
