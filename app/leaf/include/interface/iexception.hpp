//
// Created by LoicL on 29/11/2020.
//

#ifndef __LEAF_IEXCEPTION_HPP__
#define __LEAF_IEXCEPTION_HPP__

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>

#include <exception>

namespace leaf::interface
{
class IException : public boost::exception, public std::exception
{
  public:
    const char *what() const noexcept override = 0;
};
}// namespace leaf::interface

#endif// __LEAF_IEXCEPTION_HPP__
