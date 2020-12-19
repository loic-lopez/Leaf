//
// Created by LoicL on 23/11/2020.
//

#include "server/leaf_build.hpp"
#include "server/leaf_server.hpp"

using namespace Leaf::LeafServer;

LeafServer::LeafServer() : _thread(), _threadMustBeKilled(false) {

}

LeafServer::~LeafServer() {
    join();
}

void LeafServer::onStart() const {
    std::cout << "Starting thread: " << LeafVersion
              << ", build type: " << LeafBuildType
              << ", build date: " << LeafBuildDate << std::endl;
}

LeafServer &LeafServer::initialize(const Leaf::Models::ServerConfiguration &serverConfiguration) {
    (void) serverConfiguration;

    return *this;
}

void LeafServer::join() {
    if (_thread.joinable() && !_threadMustBeKilled) {
        _threadMustBeKilled = true;
        _thread.join();
    }
}

void LeafServer::start() {
    onStart();
    _thread = std::thread(&LeafServer::serve, this);
}

void LeafServer::serve() {

}