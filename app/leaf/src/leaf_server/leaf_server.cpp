//
// Created by LoicL on 23/11/2020.
//

#include "leaf_server/configuration_loader/leaf_server_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"
#include "stream/synced_cerr.hpp"
#include "stream/synced_cout.hpp"

#include <syncstream>
#include <utility>

namespace leaf::server
{

LeafServer::LeafServer(std::string serverIniPath) : _serverIniPath(std::move(serverIniPath)), _signals(_ioContext), _acceptor(_ioContext)
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
  stream::synced_cout << "Starting Leaf thread listening on: " << _serverConfiguration->listenAddr << ":" << _serverConfiguration->port
                      << std::endl;

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
  stream::synced_cout << "Shutting down Leaf thread listening on: " << _serverConfiguration->listenAddr << ":" << _serverConfiguration->port
                      << std::endl;
  _acceptor.close();
  // connection_manager_.stop_all(); TODO:
  stream::synced_cout << "Successfully shutdown Leaf thread listening on: " << _serverConfiguration->listenAddr << ":"
                      << _serverConfiguration->port << std::endl;
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
    stream::synced_cerr << "Leaf thread encountered an error:" << std::endl;
    stream::synced_cerr << iniParserError.what() << std::endl;
  }
  catch (...)
  {
    stream::synced_cerr << "Leaf thread encountered an unknown error:" << std::endl;
    stream::synced_cerr << boost::current_exception_diagnostic_information() << std::endl;
  }
}

void LeafServer::loadConfiguration()
{
  configuration_loader::LeafServerConfigurationLoader serverConfigurationLoader;

  stream::synced_cout << "Leaf thread loading configuration file: " << _serverIniPath << std::endl;

  _serverConfiguration = serverConfigurationLoader.load(_serverIniPath);

  stream::synced_cout << "Leaf thread successfully loaded configuration file: " << _serverIniPath << std::endl;
}

void LeafServer::run()
{
  stream::synced_cout << "Running Leaf thread listening on: " << _serverConfiguration->listenAddr << ":" << _serverConfiguration->port
                      << std::endl;
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
