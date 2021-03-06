//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP

#include "abstracts/ini_configuration_loader.hpp"
#include "server/models/leaf_main_server_configuration.hpp"

namespace Leaf::LeafServer::ConfigurationLoaders {
    class LeafMainServerConfigurationLoader
            : public Abstracts::INIConfigurationLoader<Models::LeafMainServerConfiguration> {
    public:
        inline static const char LEAF_SERVERS_SECTION[] = "LeafServers";
        inline static const char LEAF_CONFIGURATION_SECTION[] = "LeafConfiguration";
        inline static const char HTTP_CONFIGURATION_SECTION[] = "HttpConfiguration";

    public:
        Models::LeafMainServerConfiguration *load(const std::string &configFilePath) override;

        explicit LeafMainServerConfigurationLoader();
    };
}

#endif //LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
