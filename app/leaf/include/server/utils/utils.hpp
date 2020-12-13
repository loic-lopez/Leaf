//
// Created by LoicL on 23/12/2020.
//

#ifndef LEAF_UTILS_HPP
#define LEAF_UTILS_HPP

#include <string>
#include "server/utils/leaf_build.hpp"

namespace Leaf::LeafServer {
    class Utils {
    public:
        static std::string BuildInfo();
    };
}

#endif //LEAF_UTILS_HPP
