//
// Created by LoicL on 29/11/2020.
//

#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.hpp"

using namespace Leaf::Exceptions;
using namespace Leaf::LeafProcessManager;

std::unique_ptr<Models::LeafProcessManagerConfiguration>
ConfigurationLoaders::LeafProcessManagerConfigurationLoader::load(const std::string &configFilePath) {
    boost::property_tree::ptree pTree = this->initializeBoostPtree<LeafServerConfigFileNotFound>(configFilePath);
    std::string serversRootPath;
    std::string leafLogDirectory;
    std::string mimeTypesConfigFile;

    serversRootPath = pTree.get_child(LEAF_SERVERS_SECTION).get_child("servers_root_path").get_value<std::string>();
    leafLogDirectory = pTree.get_child(LEAF_CONFIGURATION_SECTION).get_child("leaf_log_directory").get_value<std::string>();
    mimeTypesConfigFile = pTree.get_child(HTTP_CONFIGURATION_SECTION).get_child("mime_types_config_file").get_value<std::string>();

    std::cout << configFilePath << " successfully loaded." << " {MOVE TO LOG}" << std::endl;

    return std::make_unique<LeafProcessManager::Models::LeafProcessManagerConfiguration>(
            serversRootPath,
            leafLogDirectory,
            mimeTypesConfigFile
    );
}

ConfigurationLoaders::LeafProcessManagerConfigurationLoader::LeafProcessManagerConfigurationLoader()
        : Abstracts::INIConfigurationLoader<std::unique_ptr, Models::LeafProcessManagerConfiguration>(
        {LEAF_CONFIGURATION_SECTION, LEAF_SERVERS_SECTION, HTTP_CONFIGURATION_SECTION}) {

}

