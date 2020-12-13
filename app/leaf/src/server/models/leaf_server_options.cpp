//
// Created by LoicL on 12/12/2020.
//

#include "server/models/leaf_server_options.hpp"

const std::string &Leaf::LeafServer::Models::ServerOptions::getServerConfigFilePath() const {
    return _serverConfigFilePath;
}

void Leaf::LeafServer::Models::ServerOptions::setServerConfigFilePath(const std::string &serverConfigFilePath) {
    _serverConfigFilePath = serverConfigFilePath;
}
