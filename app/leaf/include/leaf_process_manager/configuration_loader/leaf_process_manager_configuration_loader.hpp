//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP
#define LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP

#include "abstract/ini_configuration_loader.hpp"
#include "leaf_process_manager/leaf_process_manager_configuration.hpp"

#include <string>

namespace leaf::process_manager::configuration_loader
{

using namespace std::string_view_literals;// NOSONAR

class LeafProcessManagerConfigurationLoader : public abstract::INIConfigurationLoader<std::unique_ptr, LeafProcessManagerConfiguration>
{
  public:
    inline static const std::string_view LEAF_SERVERS_SECTION       = "LeafServers"sv;
    inline static const std::string_view LEAF_CONFIGURATION_SECTION = "LeafConfiguration"sv;
    inline static const std::string_view HTTP_CONFIGURATION_SECTION = "HttpConfiguration"sv;

    std::unique_ptr<LeafProcessManagerConfiguration> load(const std::string &configFilePath) override;
    explicit LeafProcessManagerConfigurationLoader();

  private:
    inline static const std::vector<std::string_view> _leaf_servers_section_properties = {
      {"servers_root_path"sv},
    };

    inline static const std::vector<std::string_view> _leaf_configuration_section_properties = {
      {"leaf_log_directory"sv},
    };

    inline static const std::vector<std::string_view> _http_configuration_section_properties = {
      {"mime_types_config_file"sv},
    };
};
}// namespace leaf::process_manager::configuration_loader

#endif// LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP
