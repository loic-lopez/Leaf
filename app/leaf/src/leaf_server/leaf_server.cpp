//
// Created by LoicL on 23/11/2020.
//

#include "leaf_server/configuration_loader/leaf_server_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"
#include "log/logger_factory.hpp"

#include <syncstream>
#include <utility>

namespace leaf::server
{

LeafServer::LeafServer(
  defines::Path serverIniPath, defines::Path leafLogDirectoryPath, size_t leafLogMaxFileSize, size_t leafLogMaxFiles,
  const std::size_t leafLogThreadsPerLeafServer
)
    : log::LoggerInterface(BOOST_CURRENT_FUNCTION),
      _serverIniPath(std::move(serverIniPath)),
      _leafLogDirectoryPath(std::move(leafLogDirectoryPath)),
      _leafLogMaxFileSize(leafLogMaxFileSize),
      _leafLogMaxFiles(leafLogMaxFiles),
      _leafLogThreadsPerLeafServer(leafLogThreadsPerLeafServer),
      _acceptor(_ioContext)
{
}

void LeafServer::initialize()
{
  _stdout->debug("Starting Leaf thread listening on: {0}:{1}", _serverConfiguration->listenAddr, _serverConfiguration->port);

  boost::asio::ip::tcp::resolver resolver(_ioContext);
  const boost::asio::ip::tcp::endpoint endpoint =
    *resolver.resolve(_serverConfiguration->listenAddr, std::to_string(_serverConfiguration->port)).begin();
  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(false));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  accept();
}

void LeafServer::stop()
{
  _stdout->info("Shutting down Leaf thread listening on: {0}:{1}", _serverConfiguration->listenAddr, _serverConfiguration->port);
  _acceptor.close();
  _ioContext.stop();
  // connection_manager_.stop_all(); TODO:
}

void LeafServer::join()
{
  if (_thread.joinable()) { _thread.join(); }
}

void LeafServer::start() { _thread = std::jthread(&LeafServer::serve, this); }

void LeafServer::serve()
{
  try
  {
    loadConfiguration();
    initialize();
    run();
  }
  catch (const boost::wrapexcept<class boost::property_tree::ini_parser::ini_parser_error> &iniParserError)
  {
    const auto stderrLogger = log::LoggerFactory::BasicStderrLogger(_loggerName);
    stderrLogger->error("Leaf thread encountered an error:");
    stderrLogger->error(iniParserError.what());
  }
  catch (const boost::wrapexcept<boost::system::system_error> &systemError)
  {
    _stderr->error("Leaf thread encountered an error:");
    _stderr->error(systemError.what());
  }
  catch (...)
  {
    const auto stderrLogger = log::LoggerFactory::BasicStderrLogger(_loggerName);
    stderrLogger->error("Leaf thread encountered an unknown error:");
    stderrLogger->error(boost::current_exception_diagnostic_information());
  }
}

void LeafServer::loadConfiguration()
{
  configuration_loader::LeafServerConfigurationLoader serverConfigurationLoader;

  _serverConfiguration = serverConfigurationLoader.load(_serverIniPath);
  initializeLoggers();

  _stdout->debug("Leaf thread successfully loaded configuration file: {0}", _serverIniPath.string());
}

void LeafServer::initializeLoggers()
{
  const boost::format httpServerName = boost::format("%1%_http_%2%") % _loggerName % _serverConfiguration->port;
  const boost::format stdoutFileName = boost::format("%1%/%2%.log") % _leafLogDirectoryPath % httpServerName;
  const boost::format stderrFileName = boost::format("%1%/%2%_stderr.log") % _leafLogDirectoryPath % httpServerName;

  const auto standardLoggers = log::LoggerFactory::CreateStdLoggers(
    httpServerName.str(), stdoutFileName, _leafLogMaxFileSize, _leafLogMaxFiles, _leafLogThreadsPerLeafServer
  );
  _stdout = standardLoggers.stdoutLogger;
  _stderr = standardLoggers.stderrLogger;
}

void LeafServer::run()
{
  _stdout->info("Started Leaf thread listening on: {0}:{1}", _serverConfiguration->listenAddr, _serverConfiguration->port);
  _ioContext.run();
}

void LeafServer::accept()
{
  _acceptor.async_accept(
    [this](const boost::system::error_code ec, const boost::asio::ip::tcp::socket)
    {
      // Check whether the server was stopped by a signal before this
      // completion handler had a chance to run.
      if (!_acceptor.is_open()) { return; }

      if (!ec)
      {
        /* connection_manager_.start(std::make_shared<connection>(
                 std::move(socket), connection_manager_, request_handler_));*/
      }

      accept();
    }
  );
}

}// namespace leaf::server
