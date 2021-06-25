//
// Created by LoicL on 13/12/2020.
//

#include <filesystem>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include "utils/utils.hpp"
#include "leaf_process_manager/leaf_process_manager.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.hpp"

using namespace Leaf::LeafProcessManager;

LeafProcessManager::~LeafProcessManager() = default;

void LeafProcessManager::displayBanner() const {
    std::cout << "Leaf: " << Utils::BuildInfo() << std::endl << std::endl;

    std::cout
            << R"(     .\^/.                                            .\^/.
   . |`|/| .                                        . |`|/| .
   |\|\|'|/|       _                       __       |\|\|'|/|
.--'-\`|/-''--.   | |       ___    __ _   / _|   .--'-\`|/-''--.
 \`-._\|./.-'/    | |      / _ \  / _` | | |_     \`-._\|./.-'/
  >`-._|/.-'<     | |___  |  __/ | (_| | |  _|     >`-._|/.-'<
 '~|/~~|~~\|~'    |_____|  \___|  \__,_| |_|      '~|/~~|~~\|~'
       |                                                |)" << std::endl;
}

void LeafProcessManager::waitForServers() const {
    for (const auto &leafServer : _leafServers) {
        leafServer->join();
    }
}

void LeafProcessManager::loadLeafConfiguration() {
    ConfigurationLoaders::LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;
    std::string configFilePath = _processManagerOptions->getServerConfigFilePath();
    std::filesystem::current_path(std::filesystem::path(configFilePath).parent_path());

    std::cout << "Loading leaf_server configuration at: " + configFilePath << ". {MOVE TO LOG}" << std::endl;
    _processManagerConfiguration = processManagerConfigurationLoader.load(configFilePath);

    for (auto &p : std::filesystem::recursive_directory_iterator(_processManagerConfiguration->getServersRootPath())) {
        if (p.is_regular_file()) {
            std::cout << "Creating LeafServer with config: " << p.path().string() << std::endl;
            auto leafServerPtr = std::make_shared<LeafServer::LeafServer>(p.path().string());
            _leafServers.push_back(std::move(leafServerPtr));
        }
    }

    std::cout << "Successfully loaded leaf_server configuration at: " + configFilePath << ". {MOVE TO LOG}"
              << std::endl;
}

void LeafProcessManager::startServers() const {
    for (const auto &leafServer : _leafServers)
        leafServer->start();
}

void LeafProcessManager::parseCommandLineArgs(int ac, const char **av) const {
    LeafOptionsParser optionsParser(_processManagerOptions.get());

    optionsParser.parseEnvironment();
    LeafOptionsParser::Status optionParserStatus = LeafOptionsParser::Status::NEED_DISPLAY_HELP;

    try {
        optionParserStatus = optionsParser.parseCommandLineArgs(ac, av);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        std::cout << "Displaying help: " << std::endl << std::endl;
    }

    if (optionParserStatus != LeafOptionsParser::Status::SUCCESS) {
        optionsParser.displayHelp();
        std::exit(1);
    }
}


void LeafProcessManager::start() {

    try {
        loadLeafConfiguration();
    } catch (const std::exception &exception) {
        std::cerr << "Leaf main thread encountered an error:" << std::endl;
        std::cerr << exception.what() << std::endl;
        std::exit(1);
    }


    displayBanner();

    std::cout << "Started Leaf with PID " << boost::interprocess::ipcdetail::get_current_process_id()
              << " {MOVE TO LOG}" << std::endl;

    startServers();
    waitForServers();

    std::cout << "Leaf main thread is shutting down: GoodBye" << std::endl;
}

LeafProcessManager &LeafProcessManager::GetInstance() {
    static LeafProcessManager leafProcessManager;
    return leafProcessManager;
}

