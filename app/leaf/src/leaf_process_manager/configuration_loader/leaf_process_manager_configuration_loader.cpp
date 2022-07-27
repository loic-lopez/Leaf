//
// Created by LoicL on 29/11/2020.
//

#include "exception/leaf_server_config_dir_not_found.hpp"
#include "exception/leaf_server_config_file_not_found.hpp"
#include "leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp"
#include "log/logger_factory.hpp"

#include <boost/property_tree/ptree.hpp>

#include <filesystem>
#include <limits>

namespace leaf::process_manager::configuration_loader
{

inline static constinit const auto serverRootPathKey = "servers_root_path";

inline static constinit const auto leafLogDirectoryKey = "leaf_log_directory";

inline static constinit const auto leafLogMaxFileSizeKey      = "leaf_log_max_file_size";
inline static constinit std::size_t defaultLeafLogMaxFileSize = 5;

inline static constinit const auto leafLogMaxFilesKey      = "leaf_log_max_files";
inline static constinit std::size_t defaultLeafLogMaxFiles = 5;

inline static constinit const auto leafLogThreadsPerLeafServerKey      = "leaf_log_threads_per_leaf_server";
inline static constinit std::size_t defaultLeafLogThreadsPerLeafServer = 2;

inline static constinit const auto mimeTypesConfigFileKey = "mime_types_config_file";

std::unique_ptr<LeafProcessManagerConfiguration> LeafProcessManagerConfigurationLoader::load(const std::string &configFilePath)
{
  const auto stdoutLogger                 = log::LoggerFactory::BasicStdoutLogger("process_manager_configuration_loader (Main Thread)");
  const boost::property_tree::ptree pTree = this->initializeBoostPtree<exception::LeafServerConfigFileNotFound>(configFilePath);

  const auto leafServersSection       = pTree.get_child(LEAF_SERVERS_SECTION.data());
  const auto leafConfigurationSection = pTree.get_child(LEAF_CONFIGURATION_SECTION.data());
  const auto httpConfigurationSection = pTree.get_child(HTTP_CONFIGURATION_SECTION.data());

  // server section
  const auto serversRootPath = std::filesystem::weakly_canonical(leafServersSection.get_child(serverRootPathKey).get_value<std::string>());
  checkValue(
    LEAF_SERVERS_SECTION, serverRootPathKey, configFilePath,
    [&serversRootPath]() -> bool { return !std::filesystem::exists(serversRootPath); }
  );

  // log section
  const auto leafLogDirectory =
    std::filesystem::weakly_canonical(leafConfigurationSection.get_child(leafLogDirectoryKey).get_value<std::string>());
  checkValue(
    LEAF_CONFIGURATION_SECTION, leafLogDirectoryKey, configFilePath,
    [&leafLogDirectory]() -> bool { return !std::filesystem::exists(leafLogDirectory); }
  );

  auto leafLogMaxFileSize = leafConfigurationSection.get_child(leafLogMaxFileSizeKey).get_value<std::size_t>();
  checkValue(
    LEAF_CONFIGURATION_SECTION, leafLogMaxFileSizeKey, configFilePath, leafLogMaxFileSize, defaultLeafLogMaxFileSize, stdoutLogger
  );

  auto leafLogMaxFiles = leafConfigurationSection.get_child(leafLogMaxFilesKey).get_value<std::size_t>();
  checkValue(LEAF_CONFIGURATION_SECTION, leafLogMaxFilesKey, configFilePath, leafLogMaxFiles, defaultLeafLogMaxFiles, stdoutLogger);

  auto leafLogThreadsPerLeafServer = leafConfigurationSection.get_child(leafLogThreadsPerLeafServerKey).get_value<std::size_t>();
  checkValue(
    LEAF_CONFIGURATION_SECTION, leafLogThreadsPerLeafServerKey, configFilePath, leafLogThreadsPerLeafServer,
    defaultLeafLogThreadsPerLeafServer, stdoutLogger
  );

  // http section
  const auto mimeTypesConfigFile =
    std::filesystem::weakly_canonical(httpConfigurationSection.get_child(mimeTypesConfigFileKey).get_value<std::string>());
  checkValue(
    HTTP_CONFIGURATION_SECTION, mimeTypesConfigFileKey, configFilePath,
    [&mimeTypesConfigFile]() -> bool { return !std::filesystem::exists(mimeTypesConfigFile); }
  );

  stdoutLogger->debug("{0} successfully loaded.", configFilePath);

  return std::make_unique<process_manager::LeafProcessManagerConfiguration>(
    serversRootPath.string(), leafLogDirectory.string(), leafLogMaxFileSize, leafLogMaxFiles, leafLogThreadsPerLeafServer,
    mimeTypesConfigFile.string()
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
