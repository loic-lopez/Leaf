//
// Created by LoicL on 13/12/2020.
//

#include <filesystem>
#include <source_location>

#include <boost/interprocess/detail/os_thread_functions.hpp>

#include "exception/leaf_exit_to_main.hpp"
#include "exception/leaf_server_config_dir_not_found.hpp"
#include "leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp"
#include "leaf_process_manager/leaf_process_manager.hpp"
#include "utils/utils.hpp"

namespace leaf::process_manager
{

void LeafProcessManager::displayBanner() const
{
  std::cout << "Leaf: " << utils::BuildInfo() << std::endl << std::endl;

  std::cout << R"(     .\^/.                                            .\^/.
   . |`|/| .                                        . |`|/| .
   |\|\|'|/|       _                       __       |\|\|'|/|
.--'-\`|/-''--.   | |       ___    __ _   / _|   .--'-\`|/-''--.
 \`-._\|./.-'/    | |      / _ \  / _` | | |_     \`-._\|./.-'/
  >`-._|/.-'<     | |___  |  __/ | (_| | |  _|     >`-._|/.-'<
 '~|/~~|~~\|~'    |_____|  \___|  \__,_| |_|      '~|/~~|~~\|~'
       |                                                |)"
            << std::endl;
}

void LeafProcessManager::loadLeafConfiguration()
{
  configuration_loader::LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;
  std::filesystem::path const configFilePath = _processManagerOptions->getServerConfigFilePath();
  const std::string configFilePathString = configFilePath.string();

  if (!std::filesystem::exists(configFilePath))
  {
    BOOST_THROW_EXCEPTION(exception::LeafServerConfigDirNotFound(configFilePathString, std::source_location::current()));
  }

  std::filesystem::current_path(configFilePath.parent_path());

  std::cout << "Loading leaf_server configuration at: " + configFilePathString << ". {MOVE TO LOG}" << std::endl;
  _processManagerConfiguration = processManagerConfigurationLoader.load(configFilePathString);

  for (auto &p : std::filesystem::recursive_directory_iterator(_processManagerConfiguration->getServersRootPath()))
  {
    if (p.is_regular_file())
    {
      std::cout << "Creating LeafServer with config: " << p.path().string() << std::endl;
      auto leafServerPtr = std::make_shared<server::LeafServer>(p.path().string());
      _leafServers.push_back(std::move(leafServerPtr));
    }
  }

  std::cout << "Successfully loaded leaf_server configuration at: " + configFilePath.string() << ". {MOVE TO LOG}" << std::endl;
}

void LeafProcessManager::startServers() const
{
  for (const auto &leafServer : _leafServers)
    leafServer->start();
}

void LeafProcessManager::waitForServers() const
{
  for (const auto &leafServer : _leafServers)
    leafServer->join();
}

void LeafProcessManager::parseCommandLineArgs(const int ac, const char **const av) const
{
  LeafOptionsParser optionsParser(_processManagerOptions.get());

  optionsParser.parseEnvironment();
  LeafOptionsParser::Status optionParserStatus = LeafOptionsParser::Status::NEED_DISPLAY_HELP;

  try
  {
    optionParserStatus = optionsParser.parseCommandLineArgs(ac, av);
  }
  catch (const std::exception &exception)
  {
    std::cerr << exception.what() << std::endl;
    std::cout << "Displaying help: " << std::endl << std::endl;
  }

  if (optionParserStatus != LeafOptionsParser::Status::SUCCESS)
  {
    optionsParser.displayHelp();
    throw exception::LeafExceptionWithExitStatus(1);
  }
}

void LeafProcessManager::start()
{
  try
  {
    loadLeafConfiguration();
  }
  catch (const std::exception &exception)
  {
    std::cerr << "Leaf main thread encountered an error:" << std::endl;
    std::cerr << exception.what() << std::endl;
    throw exception::LeafExceptionWithExitStatus(1);
  }

  displayBanner();

  std::cout << "Started Leaf with PID " << boost::interprocess::ipcdetail::get_current_process_id() << " {MOVE TO LOG}" << std::endl;

  startServers();
  waitForServers();

  std::cout << "Leaf main thread is shutting down: GoodBye" << std::endl;
}

LeafProcessManager &LeafProcessManager::GetInstance()
{
  static LeafProcessManager leafProcessManager;
  return leafProcessManager;
}

}// namespace leaf::process_manager