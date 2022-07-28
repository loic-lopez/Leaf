//
// Created by LoicL on 24/12/2020.
//

#ifndef __LEAF_HTTP_REQUEST_HPP__
#define __LEAF_HTTP_REQUEST_HPP__

#include "http_header.hpp"

#include <vector>

namespace leaf::http::request
{

/// A request received from a client.
class HttpRequest
{
  public:
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<HttpHeader> headers;
};

}// namespace leaf::http::request

#endif// __LEAF_HTTP_REQUEST_HPP__
