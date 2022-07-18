//
// Created by LoicL on 29/11/2020.
//

#include "exception/leaf_server_config_file_not_found.hpp"
#include "leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp"
#include "log/logger_factory.hpp"

#include <boost/property_tree/ptree.hpp>

namespace leaf::process_manager::configuration_loader
{

std::unique_ptr<LeafProcessManagerConfiguration> LeafProcessManagerConfigurationLoader::load(const std::string &configFilePath)
{
  const auto stdoutLogger = log::LoggerFactory::BasicStdoutLogger("process_manager_configuration_loader (Main Thread)");

  boost::property_tree::ptree pTree = this->initializeBoostPtree<exception::LeafServerConfigFileNotFound>(configFilePath);
  std::string serversRootPath;
  std::string leafLogDirectory;
  std::size_t leafLogMaxFileSize;
  std::size_t leafLogMaxFiles;
  std::string mimeTypesConfigFile;

  const auto leafServersSection       = pTree.get_child(LEAF_SERVERS_SECTION.data());
  const auto leafConfigurationSection = pTree.get_child(LEAF_CONFIGURATION_SECTION.data());
  const auto httpConfigurationSection = pTree.get_child(HTTP_CONFIGURATION_SECTION.data());

  // server section
  serversRootPath = leafServersSection.get_child("servers_root_path").get_value<decltype(serversRootPath)>();

  // log section
  leafLogDirectory   = leafConfigurationSection.get_child("leaf_log_directory").get_value<decltype(leafLogDirectory)>();
  leafLogMaxFileSize = leafConfigurationSection.get_child("leaf_log_max_file_size").get_value<decltype(leafLogMaxFileSize)>();
  leafLogMaxFiles    = leafConfigurationSection.get_child("leaf_log_max_files").get_value<decltype(leafLogMaxFileSize)>();

  // http section
  mimeTypesConfigFile = httpConfigurationSection.get_child("mime_types_config_file").get_value<decltype(mimeTypesConfigFile)>();

  stdoutLogger->info("{0} successfully loaded.", configFilePath);

  return std::make_unique<process_manager::LeafProcessManagerConfiguration>(
    serversRootPath, leafLogDirectory, leafLogMaxFileSize, leafLogMaxFiles, mimeTypesConfigFile
  );
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
