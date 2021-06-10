//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP

#include "abstracts/ini_configuration_loader.hpp"
#include "leaf_server/models/leaf_server_configuration.hpp"

namespace Leaf::LeafServer::ConfigurationLoaders {
    class LeafServerConfigurationLoader
            : public Abstracts::INIConfigurationLoader<Models::LeafServerConfiguration> {
    public:
        inline static const char LEAF_SERVER_SECTION[] = "LeafServer";

        Models::LeafServerConfiguration *load(const std::string &configFilePath) override;

        explicit LeafServerConfigurationLoader();
    };
}

#endif //LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
