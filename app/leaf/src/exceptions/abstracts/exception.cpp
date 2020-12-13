//
// Created by LoicL on 12/12/2020.
//

#include "exceptions/abstracts/exception.hpp"

const char *Leaf::Exceptions::Abstracts::Exception::what() const noexcept {
    return _msg.c_str();;
}

Leaf::Exceptions::Abstracts::Exception::Exception(const char *atFunction, int atLine) :
        _atFunction(atFunction), _atLine(atLine) {
    *this << boost::errinfo_api_function(atFunction)
          << boost::errinfo_at_line(atLine);
}
