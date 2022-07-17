//
// Created by LoicL on 29/11/2020.
//

#include "exception/leaf_server_config_file_not_found.hpp"
#include "leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp"

#include <boost/property_tree/ptree.hpp>

namespace leaf::process_manager::configuration_loader
{

std::unique_ptr<LeafProcessManagerConfiguration> LeafProcessManagerConfigurationLoader::load(const std::string &configFilePath)
{
  boost::property_tree::ptree pTree = this->initializeBoostPtree<exception::LeafServerConfigFileNotFound>(configFilePath);
  std::string serversRootPath;
  std::string leafLogDirectory;
  std::string mimeTypesConfigFile;

  serversRootPath     = pTree.get_child(LEAF_SERVERS_SECTION.data()).get_child("servers_root_path").get_value<std::string>();
  leafLogDirectory    = pTree.get_child(LEAF_CONFIGURATION_SECTION.data()).get_child("leaf_log_directory").get_value<std::string>();
  mimeTypesConfigFile = pTree.get_child(HTTP_CONFIGURATION_SECTION.data()).get_child("mime_types_config_file").get_value<std::string>();

  std::cout << configFilePath << " successfully loaded."
            << " {MOVE TO LOG}" << std::endl;

  return std::make_unique<process_manager::LeafProcessManagerConfiguration>(serversRootPath, leafLogDirectory, mimeTypesConfigFile);
}

LeafProcessManagerConfigurationLoader::LeafProcessManagerConfigurationLoader()
    : abstract::INIConfigurationLoader<std::unique_ptr, LeafProcessManagerConfiguration>(
      {{.name = LEAF_CONFIGURATION_SECTION, .properties = _leaf_configuration_section_properties},
       {.name = LEAF_SERVERS_SECTION, .properties = _leaf_servers_section_properties},
       {.name = HTTP_CONFIGURATION_SECTION, .properties = _http_configuration_section_properties}}
    )
{
}

}// namespace leaf::process_manager::configuration_loader
