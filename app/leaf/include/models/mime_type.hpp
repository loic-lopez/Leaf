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
        MimeType(std::string type, std::vector<std::string> extensions)
                : extensions(std::move(extensions)), type(std::move(type)) {

        }

        const std::vector<std::string> extensions;
        const std::string type;
    };

}

#endif //LEAF_MIME_TYPE_HPP
