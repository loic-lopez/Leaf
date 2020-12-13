//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_SERVER_CONFIGURATION_LOADER_HPP
#define LEAF_SERVER_CONFIGURATION_LOADER_HPP

#include "abstracts/ini_configuration_loader.hpp"
#include "server/models/leaf_server_configuration.hpp"

namespace Leaf::LeafServer::ConfigurationLoaders {
    class LeafServerConfigurationLoader : public Abstracts::INIConfigurationLoader<Models::LeafServerConfiguration> {
    public:
        inline static const char LEAF_SERVERS_SECTION[] = "LeafServers";
        inline static const char LEAF_CONFIGURATION_SECTION[] = "LeafConfiguration";
        inline static const char HTTP_CONFIGURATION_SECTION[] = "HttpConfiguration";

    public:
        Models::LeafServerConfiguration *load(const std::string &configFilePath) override;

        explicit LeafServerConfigurationLoader();
    };
}

#endif //LEAF_SERVER_CONFIGURATION_LOADER_HPP
