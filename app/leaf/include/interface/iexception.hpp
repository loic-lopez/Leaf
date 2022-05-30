//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_IEXCEPTION_HPP
#define LEAF_IEXCEPTION_HPP

#include <exception>

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>

namespace leaf::interface
{
class IException : public boost::exception, public std::exception
{
  public:
    const char *what() const noexcept override = 0;
};
}// namespace leaf::interface

#endif// LEAF_IEXCEPTION_HPP
