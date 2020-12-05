//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIG_FILE_NOT_FOUND_HPP
#define LEAF_LEAF_SERVER_CONFIG_FILE_NOT_FOUND_HPP

#include <string>
#include <utility>
#include <typeinfo>
#include "exceptions/abstracts/config_file_not_found.hpp"

#define quote(x) #x

namespace Leaf::Exceptions {
    class LeafServerConfigFileNotFound : public Exceptions::Abstracts::ConfigFileNotFound {

    public:
        explicit LeafServerConfigFileNotFound(
                const std::string &configFilePath,
                char const *atFunction,
                int atLine,
                int _errno
        ) : ConfigFileNotFound(configFilePath, atFunction, atLine, _errno) {
            ConfigFileNotFound::buildStdExceptionMessage("LeafServerConfigFileNotFound", "leaf.ini");

        }
    };
}


#endif //LEAF_LEAF_SERVER_CONFIG_FILE_NOT_FOUND_HPP
