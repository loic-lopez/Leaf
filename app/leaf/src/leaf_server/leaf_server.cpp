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
  std::string serverIniPath, std::string leafLogDirectoryPath, const std::size_t leafLogMaxFileSize, const std::size_t leafLogMaxFiles
)
    : log::LoggerInterface(BOOST_CURRENT_FUNCTION),
      _serverIniPath(std::move(serverIniPath)),
      _leafLogDirectoryPath(std::move(leafLogDirectoryPath)),
      _leafLogMaxFileSize(leafLogMaxFileSize),
      _leafLogMaxFiles(leafLogMaxFiles),
      _signals(_ioContext),
      _acceptor(_ioContext)
{
  // Register to handle the signals that indicate when the server should exit.
  // It is safe to register for the same signal multiple times in a program,
  // provided all registration for the specified signal is made through Asio.
  _signals.add(SIGINT);
  _signals.add(SIGTERM);
#if defined(SIGQUIT)
  _signals.add(SIGQUIT);
#endif// defined(SIGQUIT)

  registerSignalsAwaitStopCallback();
}

void LeafServer::initialize()
{
  _stdout->info("Starting Leaf thread listening on: {0}:{1}", _serverConfiguration->listenAddr, _serverConfiguration->port);

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
  log::LoggerFactory::Shutdown();
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
    _stderr->error("Leaf thread encountered an error:");
    _stderr->error(iniParserError.what());
  }
  catch (...)
  {
    _stderr->error("Leaf thread encountered an unknown error:");
    _stderr->error(boost::current_exception_diagnostic_information());
  }
}

void LeafServer::loadConfiguration()
{
  configuration_loader::LeafServerConfigurationLoader serverConfigurationLoader;

  _serverConfiguration = serverConfigurationLoader.load(_serverIniPath);

  initializeLoggers();

  _stdout->info("Leaf thread successfully loaded configuration file: {0}", _serverIniPath);
}

void LeafServer::initializeLoggers()
{
  const boost::format httpServerName = boost::format("%1%_http_%2%") % _loggerName % _serverConfiguration->port;
  const boost::format stdoutFileName = boost::format("%1%/%2%.log") % _leafLogDirectoryPath % httpServerName;
  const boost::format stderrFileName = boost::format("%1%/%2%_stderr.log") % _leafLogDirectoryPath % httpServerName;

  _stdout = log::LoggerFactory::CreateStdoutLogger(httpServerName.str(), stdoutFileName, _leafLogMaxFileSize, _leafLogMaxFiles);
  _stderr = log::LoggerFactory::CreateStderrLogger(httpServerName.str(), stderrFileName, _leafLogMaxFileSize, _leafLogMaxFiles);
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

void LeafServer::registerSignalsAwaitStopCallback()
{
  _signals.async_wait([this](const boost::system::error_code, const int) { stop(); });
}

void LeafServer::terminate() { _ioContext.stop(); }

}// namespace leaf::server
