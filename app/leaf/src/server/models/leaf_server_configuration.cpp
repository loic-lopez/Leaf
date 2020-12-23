//
// Created by LoicL on 19/12/2020.
//

#include <utility>
#include "server/models/leaf_server_configuration.hpp"

Leaf::LeafServer::Models::LeafServerConfiguration::LeafServerConfiguration(
        std::string serversRootPath,
        std::string leafConfigurationDirectory,
        std::string leafLogDirectory,
        std::string mimeTypesConfigFile
) :
        serversRootPath(std::move(serversRootPath)),
        leafConfigurationDirectory(std::move(leafConfigurationDirectory)),
        leafLogDirectory(std::move(leafLogDirectory)),
        mimeTypesConfigFile(std::move(mimeTypesConfigFile)) {

}
