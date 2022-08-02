//
// Created by LoicL on 13/12/2020.
//

// exceptions includes
#include "exception/leaf_exit_to_main.hpp"
#include "exception/leaf_server_config_file_not_found.hpp"
// process manager includes
#include "leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp"
#include "leaf_process_manager/leaf_process_manager.hpp"
// library includes
#include "library/constexpr_map.hpp"
#include "log/logger_factory.hpp"
#include "utils/utils.hpp"

#include <boost/current_function.hpp>
#include <boost/format.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>

#include <spdlog/cfg/argv.h>

#include <csignal>
#include <filesystem>
#include <source_location>

namespace leaf::process_manager
{

void LeafProcessManager::DisplayBanner()
{
  const auto stdoutLogger = log::LoggerFactory::BasicStdoutLogger("leaf_process_manager_main_thread_");
  stdoutLogger->info(utils::BuildInfo());
  stdoutLogger->info(utils::LeafBanner());
}

void LeafProcessManager::loadLeafConfiguration()
{
  configuration_loader::LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;
  std::filesystem::path const configFilePath = _processManagerOptions->getServerConfigFilePath();

  if (!std::filesystem::exists(configFilePath))
  {
    BOOST_THROW_EXCEPTION(exception::LeafServerConfigFileNotFound(configFilePath, errno, std::source_location::current()));
  }

  std::filesystem::current_path(configFilePath.parent_path());

  _processManagerConfiguration = processManagerConfigurationLoader.load(configFilePath);
  initializeLoggers();

  _stdout->debug("Successfully loaded main configuration at: {0}", configFilePath.string());

  std::vector<std::string> paths;

  for (auto entry = std::filesystem::recursive_directory_iterator(_processManagerConfiguration->getServersRootPath());
       entry != std::filesystem::recursive_directory_iterator(); ++entry)
  {
    auto filePath = entry->path();
    auto filenameString = filePath.filename().string();
    if (entry->is_regular_file() && entry->exists() && std::ranges::find(paths, filenameString) == paths.end())
    {
      if (filePath.extension() == ".ini")
      {
        paths.emplace_back(filenameString);
        _stdout->debug("Creating LeafServer with config: {0}", filePath.string());
        _leafServers.emplace_back(std::make_shared<server::LeafServer>(
          filePath, _processManagerConfiguration->getLeafLogDirectoryPath(), _processManagerConfiguration->getLeafLogMaxFileSize(),
          _processManagerConfiguration->getLeafLogMaxFiles(), _processManagerConfiguration->getLeafLogThreadsPerLeafServer()
        ));
      }
      else { _stderr->warn("File config {0} is not a ini file skipping...", filePath.string()); }
    }
    else if (!entry->is_directory())
    {
      _stderr->warn("File {0} cannot be considered as a leaf_server configuration skipping...", entry->path().string());
    }
  }

  _stdout->info(
    "logging thread pool scaled up to {0} threads per leaf server.", _processManagerConfiguration->getLeafLogThreadsPerLeafServer()
  );
}

void LeafProcessManager::initializeLoggers()
{
  const boost::format stdoutFileName =
    boost::format("%1%/%2%.log") % _processManagerConfiguration->getLeafLogDirectoryPath().string() % _loggerName;
  const boost::format stderrFileName =
    boost::format("%1%/%2%_stderr.log") % _processManagerConfiguration->getLeafLogDirectoryPath().string() % _loggerName;
  const boost::format loggerName = boost::format("%1%_main_thread_") % _loggerName;

  const auto standardLoggers = log::LoggerFactory::CreateStdLoggers(
    loggerName.str(), stdoutFileName, _processManagerConfiguration->getLeafLogMaxFileSize(),
    _processManagerConfiguration->getLeafLogMaxFiles()
  );

  _stdout = standardLoggers.stdoutLogger;
  _stderr = standardLoggers.stderrLogger;
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
  _stdout->info("Leaf main thread is shutting down: GoodBye");
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
    const auto stderrLogger = log::LoggerFactory::BasicStderrLogger(_loggerName);
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
  DisplayBanner();

  try
  {
    loadLeafConfiguration();
  }
  catch (const std::exception &exception)
  {
    const auto stderrLogger = log::LoggerFactory::BasicStderrLogger(_loggerName);
    stderrLogger->error("Leaf main thread encountered an error:");
    stderrLogger->error(exception.what());
    throw exception::LeafExceptionWithExitStatus(1);
  }

  _stdout->info("Started Leaf main thread with PID {0}", boost::interprocess::ipcdetail::get_current_process_id());

  startServers();
  waitForServers();
}

void LeafProcessManager::RegisterSignalHandlers()
{
  constexpr std::array<decltype(SIGINT), 3> signals
  {
    SIGINT, SIGTERM,
#if defined(SIGQUIT)
      SIGQUIT,
#endif// defined(SIGQUIT)
  };

  for (const auto &signal : signals)
  {
    std::signal(signal, LeafProcessManager::SignalHandler);
  }
}

void LeafProcessManager::SignalHandler(const int signal)
{
  using std::string_view_literals::operator""sv;
  constexpr library::ConstexprMap<decltype(SIGINT), std::string_view, 3> signals
  {
    {SIGINT, "SIGINT"sv}, {SIGTERM, "SIGTERM"sv},
#if defined(SIGQUIT)
      {SIGQUIT, "SIGQUIT"sv},
#endif// defined(SIGQUIT)
  };

  const LeafProcessManager &leafProcessManager = GetInstance();

  std::string signalName("unknown signal code ");
  if (const auto signalIt = signals.at(signal); signalIt == signals.end()) signalName += std::to_string(signal);
  else
    signalName = signalIt->second;

  leafProcessManager._stdout->warn("Signal {0} received waiting for threads to complete.", signalName);
  for (const auto &leafServer : leafProcessManager._leafServers)
    leafServer->stop();
  leafProcessManager._stdout->info("All threads completed.", signalName);
}

LeafProcessManager::LeafProcessManager() : log::LoggerInterface(BOOST_CURRENT_FUNCTION)
{
  log::LoggerFactory::InitializeFactory();

  RegisterSignalHandlers();
}

LeafProcessManager::~LeafProcessManager() { log::LoggerFactory::ShutdownGlobalThreadPool(); }

}// namespace leaf::process_manager
