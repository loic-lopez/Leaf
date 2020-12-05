//
// Created by LoicL on 29/11/2020.
//

#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "server/leaf_conf.hpp"

using namespace Leaf::Exceptions;

void Leaf::LeafServer::LeafConf::initialize(const std::string &configFilePath) {
    boost::property_tree::ptree pTree = this->initializeBoostPtree<LeafServerConfigFileNotFound>(configFilePath);

    for (const auto &c : pTree) {
        (void) c;
    }
}

