//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_MIME_TYPES_HPP
#define LEAF_MIME_TYPES_HPP

#include <vector>
#include "models/mime_type.hpp"

namespace Leaf::Models {
    class MimeTypes {
    public:
        const std::vector<MimeType> mimeTypes;

        inline static const char DEFAULT[] = "text/plain";

        std::string extensionToType(const std::string &extension) {
            for (const MimeType &mimeType : mimeTypes) {
                for (const std::string &ext : mimeType.extensions) {
                    if (ext == extension) {
                        return mimeType.type;
                    }
                }
            }

            return DEFAULT;
        }

    };
}

#endif //LEAF_MIME_TYPES_HPP
