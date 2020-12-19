//
// Created by LoicL on 13/12/2020.
//

#include "server/leaf_build.hpp"
#include "server/leaf_process_manager.hpp"

using namespace Leaf::LeafServer;

LeafProcessManager::LeafProcessManager(int ac, const char **av)
        : _ac(ac), _av(av), _leafServerOptions(new Models::LeafServerOptions) {

}

LeafProcessManager::~LeafProcessManager() {
    delete _leafServerOptions;
}

void LeafProcessManager::onStart() {
    std::cout << "Starting Leaf: " << LeafVersion
              << ", build type: " << LeafBuildType
              << ", build date: " << LeafBuildDate << std::endl;
}

void LeafProcessManager::waitForServers() {
    for (LeafServer &leafServer : this->_leafServers) {
        leafServer.join();
    }
}

void LeafProcessManager::loadConfiguration() {
    LeafServerOptionsParser serverOptionsParser(_leafServerOptions);

    serverOptionsParser.parseEnvironment();
    if (serverOptionsParser.parseCommandLineArgs(_ac, _av) != LeafServerOptionsParser::Status::SUCCESS) {
        serverOptionsParser.displayHelp();

    }
}

void LeafProcessManager::start() {
    onStart();
    loadConfiguration();
    waitForServers();
}
