//
// Created by LoicL on 23/11/2020.
//

#include <utility>
#include <syncstream>

#include "streams/synced_cout.hpp"
#include "streams/synced_cerr.hpp"
#include "leaf_server/configuration_loaders/leaf_server_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"

using namespace Leaf;

LeafServer::LeafServer::LeafServer(std::string serverIniPath)
        : _serverIniPath(std::move(serverIniPath)),
          _signals(_ioContext),
          _acceptor(_ioContext) {

    // Register to handle the signals that indicate when the server should exit.
    // It is safe to register for the same signal multiple times in a program,
    // provided all registration for the specified signal is made through Asio.
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
#if defined(SIGQUIT)
    _signals.add(SIGQUIT);
#endif // defined(SIGQUIT)

    registerSignalsAwaitStopCallback();
}

void LeafServer::LeafServer::initialize() {
    Streams::synced_cout << "Starting Leaf thread listening on: "
                                << _serverConfiguration->listenAddr
                                << ":" << _serverConfiguration->port
                                << std::endl;

    boost::asio::ip::tcp::resolver resolver(_ioContext);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(_serverConfiguration->listenAddr,
                                                                std::to_string(_serverConfiguration->port)).begin();
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(false));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    accept();
}

void LeafServer::LeafServer::stop() {
    Streams::synced_cout << "Shutting down Leaf thread listening on: "
                                << _serverConfiguration->listenAddr
                                << ":" << _serverConfiguration->port
                                << std::endl;
    _acceptor.close();
    // connection_manager_.stop_all(); TODO:
    Streams::synced_cout << "Successfully shutdown Leaf thread listening on: "
                                << _serverConfiguration->listenAddr
                                << ":" << _serverConfiguration->port
                                << std::endl;
}

void LeafServer::LeafServer::join() {
    if (_thread.joinable()) {
        _thread.join();
    }
}

void LeafServer::LeafServer::start() {
    _thread = std::jthread(&LeafServer::serve, this);
}

void LeafServer::LeafServer::serve() {
    try {
        loadConfiguration();
        initialize();
        run();
    } catch (const boost::wrapexcept<class boost::property_tree::ini_parser::ini_parser_error> &ini_parser_error) {
        Streams::synced_cerr << "Leaf thread encountered an error:" << std::endl;
        Streams::synced_cerr << ini_parser_error.what() << std::endl;
    } catch (...) {
        Streams::synced_cerr << "Leaf thread encountered an unknown error:" << std::endl;
        Streams::synced_cerr << boost::current_exception_diagnostic_information() << std::endl;
    }
}

void LeafServer::LeafServer::loadConfiguration() {
    ConfigurationLoaders::LeafServerConfigurationLoader serverConfigurationLoader;

    Streams::synced_cout << "Leaf thread loading configuration file: " << _serverIniPath << std::endl;

    _serverConfiguration = serverConfigurationLoader.load(_serverIniPath);

    Streams::synced_cout << "Leaf thread successfully loaded configuration file: " << _serverIniPath << std::endl;
}


void LeafServer::LeafServer::run() {
    Streams::synced_cout << "Running Leaf thread listening on: "
                                << _serverConfiguration->listenAddr
                                << ":" << _serverConfiguration->port
                                << std::endl;
    _ioContext.run();
}

void LeafServer::LeafServer::accept() {
    _acceptor.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket) {
        // Check whether the server was stopped by a signal before this
        // completion handler had a chance to run.
        if (!_acceptor.is_open()) {
            return;
        }

        if (!ec) {
            /* connection_manager_.start(std::make_shared<connection>(
                     std::move(socket), connection_manager_, request_handler_));*/
        }

        accept();
    });
}

void LeafServer::LeafServer::registerSignalsAwaitStopCallback() {
    _signals.async_wait(
            [this](boost::system::error_code, int) {
                stop();
            });
}

void LeafServer::LeafServer::terminate() {
    _ioContext.stop();
}
