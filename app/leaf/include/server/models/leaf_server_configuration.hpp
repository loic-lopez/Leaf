//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_HPP

#include <string>

namespace Leaf::LeafServer::Models {

    class LeafServerConfiguration {
    public:
        explicit LeafServerConfiguration(
                std::string serversRootPath,
                std::string leafConfigurationDirectory,
                std::string leafLogDirectory,
                std::string mimeTypesConfigFile);

        const std::string serversRootPath;
        const std::string leafConfigurationDirectory;
        const std::string leafLogDirectory;
        const std::string mimeTypesConfigFile;


    };

}


#endif // LEAF_LEAF_SERVER_CONFIGURATION_HPP