//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_SERVER_CONFIGURATION_LOADER_HPP
#define LEAF_SERVER_CONFIGURATION_LOADER_HPP

#include "server/models/leaf_server_config.hpp"
#include "abstracts/ini_configuration_loader.hpp"

namespace Leaf::LeafServer::ConfigurationLoaders {
    class ServerConfiguration
            : public Abstracts::INIConfigurationLoader<Leaf::LeafServer::Models::LeafServerConfiguration> {
    public:
        Leaf::LeafServer::Models::LeafServerConfiguration load(const std::string &configFilePath) override;
    };
}

#endif //LEAF_SERVER_CONFIGURATION_LOADER_HPP
