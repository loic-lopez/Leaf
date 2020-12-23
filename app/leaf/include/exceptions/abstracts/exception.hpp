//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_EXCEPTION_HPP
#define LEAF_EXCEPTION_HPP

#include <string>
#include <utility>
#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/errinfo_at_line.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <iostream>
#include "interfaces/iexception.hpp"
#include "concepts/leaf_concepts.hpp"

namespace Leaf::Exceptions::Abstracts {

    class Exception : public Interfaces::IException {
    protected:
        char const *_atFunction;
        std::string _msg;
        int _atLine;

        virtual void buildStdExceptionMessage(const char *exceptionClassName) = 0;

    public:
        explicit Exception(char const *atFunction, int atLine);

        const char *what() const noexcept override;
    };
}

#endif //LEAF_EXCEPTION_HPP
