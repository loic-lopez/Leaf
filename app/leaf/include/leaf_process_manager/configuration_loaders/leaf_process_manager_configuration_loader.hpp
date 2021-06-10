//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP
#define LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP

#include "abstracts/ini_configuration_loader.hpp"
#include "leaf_process_manager/models/leaf_process_manager_configuration.hpp"

namespace Leaf::LeafProcessManager::ConfigurationLoaders {
    class LeafProcessManagerConfigurationLoader
            : public Abstracts::INIConfigurationLoader<Models::LeafProcessManagerConfiguration> {
    public:
        inline static const char LEAF_SERVERS_SECTION[] = "LeafServers";
        inline static const char LEAF_CONFIGURATION_SECTION[] = "LeafConfiguration";
        inline static const char HTTP_CONFIGURATION_SECTION[] = "HttpConfiguration";

        Models::LeafProcessManagerConfiguration *load(const std::string &configFilePath) override;

        explicit LeafProcessManagerConfigurationLoader();
    };
}

#endif //LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP
