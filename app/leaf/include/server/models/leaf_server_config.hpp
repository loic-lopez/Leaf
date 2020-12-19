//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIG_HPP
#define LEAF_LEAF_SERVER_CONFIG_HPP

#include <string>

namespace Leaf::LeafServer::Models {

    class LeafServerConfiguration {
    private:
        std::string _serversRootPath;
        std::string _leafConfigurationDirectory;
        std::string _mimeTypesConfigFile;

    };

}


#endif //LEAF_LEAF_SERVER_CONFIG_HPP
