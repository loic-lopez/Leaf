//
// Created by LoicL on 23/11/2020.
//

#include "leaf_server/configuration_loaders/leaf_server_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"

#include <utility>

using namespace Leaf::LeafServer;

LeafServer::LeafServer(std::string serverIniPath)
        : _thread(), _threadMustBeKilled(false), _serverIniPath(std::move(serverIniPath)),
          _ioContext(1),
          _signals(_ioContext),
          _acceptor(_ioContext) {

}

LeafServer::LeafServer(const LeafServer &leafServer)
        : _thread(), _threadMustBeKilled(false), _serverIniPath(leafServer._serverIniPath),
          _ioContext(1),
          _signals(_ioContext),
          _acceptor(_ioContext) {

}

LeafServer::~LeafServer() {
    join();
}

void LeafServer::onStart() const {
    std::cout << "Starting Leaf thread: listening on "
              << _serverConfiguration->listenAddr
              << ":" << _serverConfiguration->port
              << std::endl;
}

void LeafServer::stop() {

}

void LeafServer::join() {
    if (_thread.joinable() && !_threadMustBeKilled) {
        _threadMustBeKilled = true;
        _thread.join();
    }
}

void LeafServer::start() {
    _thread = std::thread(&LeafServer::serve, this);
}

void LeafServer::serve() {
    loadConfiguration();
    onStart();
}

void LeafServer::loadConfiguration() {
    ConfigurationLoaders::LeafServerConfigurationLoader serverConfigurationLoader;

    _serverConfiguration.reset(serverConfigurationLoader.load(_serverIniPath));
}

void LeafServer::accept() {

}

