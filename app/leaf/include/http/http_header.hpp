//
// Created by LoicL on 24/12/2020.
//

#ifndef __LEAF_HTTP_HEADER_HPP__
#define __LEAF_HTTP_HEADER_HPP__

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

#endif// __LEAF_HTTP_HEADER_HPP__
