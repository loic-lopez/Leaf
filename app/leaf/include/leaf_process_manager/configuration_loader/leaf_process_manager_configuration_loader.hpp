//
// Created by LoicL on 29/11/2020.
//

#ifndef __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP__
#define __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP__

#include "abstract/ini_configuration_loader.hpp"
#include "leaf_process_manager/leaf_process_manager_configuration.hpp"

#include <string>

namespace leaf::process_manager::configuration_loader
{

using std::string_view_literals::operator""sv;

class LeafProcessManagerConfigurationLoader : public abstract::INIConfigurationLoader<std::unique_ptr, LeafProcessManagerConfiguration>
{
  public:
    inline static constinit const defines::ini::Section LEAF_SERVERS_SECTION       = "LeafServers"sv;
    inline static constinit const defines::ini::Section LEAF_CONFIGURATION_SECTION = "LeafConfiguration"sv;
    inline static constinit const defines::ini::Section HTTP_CONFIGURATION_SECTION = "HttpConfiguration"sv;

    std::unique_ptr<LeafProcessManagerConfiguration> load(const defines::Path &configFilePath) override;
    explicit LeafProcessManagerConfigurationLoader();
    virtual ~LeafProcessManagerConfigurationLoader() = default;

  private:
    inline static const defines::ini::PropertiesContainer _leaf_servers_section_properties = {
      {"servers_root_path"sv},
    };

    inline static const defines::ini::PropertiesContainer _leaf_configuration_section_properties = {
      {"leaf_log_directory"sv},
    };

    inline static const defines::ini::PropertiesContainer _http_configuration_section_properties = {
      {"mime_types_config_file"sv},
    };
};
}// namespace leaf::process_manager::configuration_loader

#endif// __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_LOADER_HPP__
