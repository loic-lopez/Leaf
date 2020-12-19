//
// Created by LoicL on 17/12/2020.
//

#ifndef LEAF_MIME_TYPE_HPP
#define LEAF_MIME_TYPE_HPP

#include <string>
#include <utility>
#include <vector>

namespace Leaf::Models {

    class MimeType {
    public:
        MimeType(std::string extension, std::vector<std::string> types)
                : extension(std::move(extension)), types(std::move(types)) {

        }

    public:
        const std::string extension;
        const std::vector<std::string> types;
    };

}

#endif //LEAF_MIME_TYPE_HPP
