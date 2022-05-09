//
// Created by LoicL on 12/12/2020.
//

#include "exception/abstract/exception.hpp"

namespace leaf::exception::abstract
{

const char *Exception::what() const noexcept { return _msg.c_str(); }

Exception::Exception(const std::source_location &sourceLocation) : _sourceLocation(sourceLocation)
{
  *this << boost::errinfo_api_function(_sourceLocation.function_name()) << boost::errinfo_at_line(static_cast<int>(_sourceLocation.line()));
}

}// namespace leaf::exception::abstract
