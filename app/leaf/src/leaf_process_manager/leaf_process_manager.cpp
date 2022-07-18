//
// Created by LoicL on 13/12/2020.
//

#include "exception/leaf_exit_to_main.hpp"
#include "exception/leaf_server_config_dir_not_found.hpp"
#include "leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp"
#include "leaf_process_manager/leaf_process_manager.hpp"
#include "log/logger_factory.hpp"
#include "utils/utils.hpp"

#include <boost/current_function.hpp>
#include <boost/format.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>

#include <spdlog/cfg/argv.h>

#include <filesystem>
#include <source_location>

namespace leaf::process_manager
{

void LeafProcessManager::displayBanner()
{
  std::cout << utils::BuildInfo() << std::endl;
  std::cout << utils::LeafBanner() << std::endl;
}

void LeafProcessManager::loadLeafConfiguration()
{
  auto stdoutLogger = log::LoggerFactory::BasicStdoutLogger(_loggerName);

  configuration_loader::LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;
  std::filesystem::path const configFilePath = _processManagerOptions->getServerConfigFilePath();
  const std::string configFilePathString     = configFilePath.string();

  if (!std::filesystem::exists(configFilePath))
  {
    BOOST_THROW_EXCEPTION(exception::LeafServerConfigDirNotFound(configFilePathString, std::source_location::current()));
  }

  std::filesystem::current_path(configFilePath.parent_path());

  _processManagerConfiguration = processManagerConfigurationLoader.load(configFilePathString);

  {
    const boost::format stdoutFileName =
      boost::format("%1%/%2%.log") % _processManagerConfiguration->getLeafLogDirectoryPath() % _loggerName;
    const boost::format stderrFileName =
      boost::format("%1%/%2%_stderr.log") % _processManagerConfiguration->getLeafLogDirectoryPath() % _loggerName;
    const boost::format loggerName = boost::format("%1% (Main Thread)") % _loggerName;

    _stdout = log::LoggerFactory::CreateStdoutLogger(
      loggerName.str(), stdoutFileName, _processManagerConfiguration->getLeafLogMaxFileSize(), _processManagerConfiguration->getLeafLogMaxFiles()
    );

    _stderr = log::LoggerFactory::CreateStderrLogger(
      loggerName.str(), stderrFileName, _processManagerConfiguration->getLeafLogMaxFileSize(), _processManagerConfiguration->getLeafLogMaxFiles()
    );
  }

  _stdout->info("Loading leaf_server configuration at: {0}", configFilePathString);

  for (auto &p : std::filesystem::recursive_directory_iterator(_processManagerConfiguration->getServersRootPath()))
  {
    if (p.is_regular_file())
    {
      std::string pathString = p.path().string();
      _stdout->info("Creating LeafServer with config: {0}", pathString);
      _leafServers.emplace_back(std::make_shared<server::LeafServer>(
        pathString, _processManagerConfiguration->getLeafLogDirectoryPath(), _processManagerConfiguration->getLeafLogMaxFileSize(),
        _processManagerConfiguration->getLeafLogMaxFiles()
      ));
    }
  }

  _stdout->info("Successfully loaded leaf_server configuration at: {0}", configFilePath.string());
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
  spdlog::cfg::load_argv_levels(ac, av);
  LeafOptionsParser optionsParser(_processManagerOptions.get());

  optionsParser.parseEnvironment();
  LeafOptionsParser::Status optionParserStatus = LeafOptionsParser::Status::NEED_DISPLAY_HELP;

  try
  {
    optionParserStatus = optionsParser.parseCommandLineArgs(ac, av);
  }
  catch (const std::exception &exception)
  {
    auto stderrLogger = log::LoggerFactory::BasicStderrLogger(_loggerName);
    stderrLogger->error(exception.what());
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
  displayBanner();

  try
  {
    loadLeafConfiguration();
  }
  catch (const std::exception &exception)
  {
    auto stderrLogger = log::LoggerFactory::BasicStderrLogger(_loggerName);
    stderrLogger->error("Leaf main thread encountered an error:");
    stderrLogger->error(exception.what());
    throw exception::LeafExceptionWithExitStatus(1);
  }

  _stdout->info("Started Leaf main thread with PID {0}", boost::interprocess::ipcdetail::get_current_process_id());

  startServers();
  waitForServers();
  log::LoggerFactory::Shutdown();

  _stdout->info("Leaf main thread is shutting down: GoodBye");
}

LeafProcessManager &LeafProcessManager::GetInstance()
{
  static LeafProcessManager leafProcessManager;
  return leafProcessManager;
}

LeafProcessManager::LeafProcessManager() : log::LoggerInterface(BOOST_CURRENT_FUNCTION) { log::LoggerFactory::InitializeFactory(); }

}// namespace leaf::process_manager