//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_HTTP_HEADER_HPP
#define LEAF_HTTP_HEADER_HPP

#include <string>

namespace Leaf::Models::Http {
    class HttpHeader {
    public:
        std::string name;
        std::string value;
    };
}

#endif //LEAF_HTTP_HEADER_HPP
