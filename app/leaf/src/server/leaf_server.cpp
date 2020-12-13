//
// Created by LoicL on 23/11/2020.
//

#include "server/leaf_build.hpp"
#include "server/leaf_server.hpp"

void Leaf::LeafServer::LeafServer::onStart() const {
    std::cout << "Starting Leaf: " << LeafVersion
              << ", build type: " << LeafBuildType
              << ", build date: " << LeafBuildDate << std::endl;
}

void Leaf::LeafServer::LeafServer::initialize(const Leaf::LeafServer::Models::ServerOptions &leafServerOptions) {
    (void) leafServerOptions;
}
