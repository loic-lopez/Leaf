//
// Created by LoicL on 12/12/2020.
//

#include "exceptions/abstracts/exception.hpp"

const char *Leaf::Exceptions::Abstracts::Exception::what() const noexcept {
    return _msg.c_str();
}

Leaf::Exceptions::Abstracts::Exception::Exception(const boost::source_location &sourceLocation) : _sourceLocation(sourceLocation)
{
    *this << boost::errinfo_api_function(_sourceLocation.function_name())
          << boost::errinfo_at_line(_sourceLocation.line());
}
