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
        std::string _msg;
        boost::source_location _sourceLocation;

        virtual void buildStdExceptionMessage(const char *exceptionClassName) = 0;

    public:
        explicit Exception(const boost::source_location &sourceLocation);

        const char *what() const noexcept override;
    };
}

#endif //LEAF_EXCEPTION_HPP
