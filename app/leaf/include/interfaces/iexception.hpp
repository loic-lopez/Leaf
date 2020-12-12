//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_IEXCEPTION_HPP
#define LEAF_IEXCEPTION_HPP

#include <exception>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

namespace Leaf::Interfaces {
    class IException : public boost::exception, public std::exception {
    public:
        const char *what() const noexcept override = 0;
    };
}

#endif //LEAF_IEXCEPTION_HPP
