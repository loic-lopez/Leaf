//
// Created by LoicL on 29/11/2020.
//

#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "server/configuration_loaders/leaf_server_configuration_loader.hpp"

using namespace Leaf::Exceptions;
using namespace Leaf::LeafServer;

Models::LeafServerConfiguration *
ConfigurationLoaders::LeafServerConfigurationLoader::load(const std::string &configFilePath) {
    boost::property_tree::ptree pTree = this->initializeBoostPtree<LeafServerConfigFileNotFound>(configFilePath);
    std::string serversRootPath;
    std::string leafConfigurationDirectory;
    std::string leafLogDirectory;
    std::string mimeTypesConfigFile;

    serversRootPath = pTree.find(LEAF_SERVERS_SECTION)->second
            .find("servers_root_path")->second.get_value<std::string>();
    leafConfigurationDirectory = pTree.find(LEAF_CONFIGURATION_SECTION)->second
            .find("leaf_configuration_directory")->second.get_value<std::string>();
    leafLogDirectory = pTree.find(LEAF_CONFIGURATION_SECTION)->second
            .find("leaf_log_directory")->second.get_value<std::string>();
    mimeTypesConfigFile = pTree.find(HTTP_CONFIGURATION_SECTION)->second
            .find("mime_types_config_file")->second.get_value<std::string>();

    std::cout << configFilePath << " successfully loaded." << " {MOVE TO LOG}" << std::endl;

    return new Leaf::LeafServer::Models::LeafServerConfiguration{
            serversRootPath,
            leafConfigurationDirectory,
            leafLogDirectory,
            mimeTypesConfigFile
    };
}

ConfigurationLoaders::LeafServerConfigurationLoader::LeafServerConfigurationLoader()
        : INIConfigurationLoader({LEAF_CONFIGURATION_SECTION, LEAF_SERVERS_SECTION, HTTP_CONFIGURATION_SECTION}) {

}

