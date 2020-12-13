//
// Created by LoicL on 23/11/2020.
//

#include "server/leaf_server.hpp"

#include <utility>

using namespace Leaf::LeafServer;

LeafServer::LeafServer() : _thread(), _threadMustBeKilled(false) {

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
    onStart();
}

LeafServer *LeafServer::loadConfiguration(const std::string &serverIniPath) {
    (void) serverIniPath;
    return this;
}
