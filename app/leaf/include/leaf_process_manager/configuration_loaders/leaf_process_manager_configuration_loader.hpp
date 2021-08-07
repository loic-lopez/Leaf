//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP
#define LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP

#include <string>
#include "abstracts/ini_configuration_loader.hpp"
#include "leaf_process_manager/models/leaf_process_manager_configuration.hpp"

namespace Leaf::LeafProcessManager::ConfigurationLoaders {
    class LeafProcessManagerConfigurationLoader
            : public Abstracts::INIConfigurationLoader<std::unique_ptr, Models::LeafProcessManagerConfiguration> {
    private:
        inline static const std::vector<std::string> _leaf_servers_section_properties = {
                {"servers_root_path"},
        };

        inline static const std::vector<std::string> _leaf_configuration_section_properties = {
                {"leaf_log_directory"},
        };

        inline static const std::vector<std::string> _http_configuration_section_properties = {
                {"mime_types_config_file"},
        };

    public:
        inline static const std::string LEAF_SERVERS_SECTION = "LeafServers";
        inline static const std::string LEAF_CONFIGURATION_SECTION = "LeafConfiguration";
        inline static const std::string HTTP_CONFIGURATION_SECTION = "HttpConfiguration";

        std::unique_ptr<Models::LeafProcessManagerConfiguration> load(const std::string &configFilePath) override;

        explicit LeafProcessManagerConfigurationLoader();
    };
}

#endif //LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP
