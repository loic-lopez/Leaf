//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_SERVER_CONFIG_FILE_NOT_FOUND_HPP
#define LEAF_SERVER_CONFIG_FILE_NOT_FOUND_HPP

#include "exceptions/abstracts/config_file_not_found.hpp"

namespace Leaf::Exceptions {
    class LeafServerConfigFileNotFound : public Exceptions::Abstracts::ConfigFileNotFound {

    public:
        explicit LeafServerConfigFileNotFound(
                const std::string &configFilePath,
                int _errno,
                const boost::source_location &location
        );
    };
}


#endif //LEAF_SERVER_CONFIG_FILE_NOT_FOUND_HPP
