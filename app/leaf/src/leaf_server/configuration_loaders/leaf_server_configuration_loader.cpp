//
// Created by LoicL on 06/03/2021.
//

#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "leaf_server/configuration_loaders/leaf_server_configuration_loader.hpp"

using namespace Leaf::Exceptions;
using namespace Leaf::LeafServer;

std::shared_ptr<Models::LeafServerConfiguration>
ConfigurationLoaders::LeafServerConfigurationLoader::load(const std::string &configFilePath) {
    boost::property_tree::ptree pTree = this->initializeBoostPtree<LeafServerConfigFileNotFound>(configFilePath);
    int port;
    std::string documentRootPath;
    std::string listenAddr;

    port = pTree.find(LEAF_SERVER_SECTION)->second.find("port")->second.get_value<int>();
    documentRootPath = pTree.find(LEAF_SERVER_SECTION)->second.find("port")->second.get_value<std::string>();
    listenAddr = pTree.find(LEAF_SERVER_SECTION)->second.find("listen_addr")->second.get_value<std::string>();

    return std::make_shared<Models::LeafServerConfiguration>(port, documentRootPath, listenAddr);
}

ConfigurationLoaders::LeafServerConfigurationLoader::LeafServerConfigurationLoader()
        : INIConfigurationLoader<std::shared_ptr, Models::LeafServerConfiguration>({LEAF_SERVER_SECTION}) {

}
