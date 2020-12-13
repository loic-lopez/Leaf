//
// Created by LoicL on 12/12/2020.
//

#include "server/models/leaf_server_options.hpp"

const std::string &Leaf::LeafServer::Models::LeafServerOptions::getServerConfigFilePath() const {
    return _serverConfigFilePath;
}

void Leaf::LeafServer::Models::LeafServerOptions::setServerConfigFilePath(const std::string &serverConfigFilePath) {
    _serverConfigFilePath = serverConfigFilePath;
}
