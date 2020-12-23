//
// Created by LoicL on 13/12/2020.
//

#include "server/utils/utils.hpp"
#include "server/leaf_process_manager.hpp"
#include "server/configuration_loaders/leaf_server_configuration_loader.hpp"

using namespace Leaf::LeafServer;

LeafProcessManager::LeafProcessManager(int ac, const char **av)
        : _ac(ac), _av(av), _leafServerOptions(new Models::LeafServerOptions) {

}

LeafProcessManager::~LeafProcessManager() {
    delete _leafServerOptions;
}

void LeafProcessManager::onStart() {
    std::cout << "Starting Leaf: " << Utils::BuildInfo() << std::endl;
}

void LeafProcessManager::waitForServers() {
    for (LeafServer &leafServer : this->_leafServers) {
        leafServer.join();
    }
}

void LeafProcessManager::loadLeafConfiguration() {
    ConfigurationLoaders::LeafServerConfigurationLoader serverConfigurationLoader;

    _leafServerConfiguration = serverConfigurationLoader.load(_leafServerOptions->getServerConfigFilePath());
}

void LeafProcessManager::startServers() {
}

void LeafProcessManager::parseCommandLineArgs() {
    LeafServerOptionsParser serverOptionsParser(_leafServerOptions);

    serverOptionsParser.parseEnvironment();
    LeafServerOptionsParser::Status leafServerOptionParserStatus = LeafServerOptionsParser::Status::NEED_DISPLAY_HELP;

    try {
        leafServerOptionParserStatus = serverOptionsParser.parseCommandLineArgs(_ac, _av);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        std::cout << "Displaying help: " << std::endl << std::endl;
    }

    if (leafServerOptionParserStatus != LeafServerOptionsParser::Status::SUCCESS) {
        serverOptionsParser.displayHelp();
        std::exit(1);
    }
}


void LeafProcessManager::start() {
    parseCommandLineArgs();
    onStart();
    loadLeafConfiguration();
    startServers();
    waitForServers();
}