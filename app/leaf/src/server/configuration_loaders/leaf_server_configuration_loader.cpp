//
// Created by LoicL on 29/11/2020.
//

#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "server/configuration_loaders/leaf_server_configuration_loader.hpp"

using namespace Leaf::Exceptions;

void Leaf::LeafServer::ConfigurationLoaders::ServerConfiguration::load(const std::string &configFilePath) {
    boost::property_tree::ptree pTree = this->initializeBoostPtree<LeafServerConfigFileNotFound>(configFilePath);

    for (const auto &c : pTree) {
        (void) c;
    }
}

/*
const std::string &Leaf::LeafServer::ServerConfiguration::getServersRootPath() const {
    return _serversRootPath;
}

const std::string &Leaf::LeafServer::ServerConfiguration::getMimeTypesFilePath() const {
    return _mimeTypesFilePath;
}
*/
