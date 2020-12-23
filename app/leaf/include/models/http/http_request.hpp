//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_HTTP_REQUEST_HPP
#define LEAF_HTTP_REQUEST_HPP

#include <vector>
#include "models/http/http_header.hpp"

namespace Leaf::Models::Http {

    /// A request received from a client.
    class HttpRequest {
    public:
        std::string method;
        std::string uri;
        int http_version_major;
        int http_version_minor;
        std::vector<HttpHeader> headers;
    };

}

#endif //LEAF_HTTP_REQUEST_HPP
