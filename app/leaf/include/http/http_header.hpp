//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_HTTP_HEADER_HPP
#define LEAF_HTTP_HEADER_HPP

#include <string>

namespace leaf::http
{

class HttpHeader
{
  public:
    std::string name;
    std::string value;
};

}// namespace leaf::http

#endif// LEAF_HTTP_HEADER_HPP
