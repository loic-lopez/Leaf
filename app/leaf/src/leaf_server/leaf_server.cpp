//
// Created by LoicL on 23/11/2020.
//

#include <utility>
#include <syncstream>

#include "leaf_server/configuration_loaders/leaf_server_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"

using namespace Leaf::LeafServer;

LeafServer::LeafServer(std::string serverIniPath)
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

void LeafServer::initialize() {
    std::osyncstream(std::cout) << "Starting Leaf thread listening on: "
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

void LeafServer::stop() {
    std::osyncstream(std::cout) << "Shutting down Leaf thread listening on: "
                                << _serverConfiguration->listenAddr
                                << ":" << _serverConfiguration->port
                                << std::endl;
    _acceptor.close();
    // connection_manager_.stop_all(); TODO:
    std::osyncstream(std::cout) << "Successfully shutdown Leaf thread listening on: "
                                << _serverConfiguration->listenAddr
                                << ":" << _serverConfiguration->port
                                << std::endl;
}

void LeafServer::join() {
    if (_thread.joinable()) {
        _thread.join();
    }
}

void LeafServer::start() {
    _thread = std::jthread(&LeafServer::serve, this);
}

void LeafServer::serve() {
    try {
        loadConfiguration();
        initialize();
        run();
    } catch (const boost::exception &exception) {
        std::osyncstream(std::cerr) << "Leaf thread listening on: "
        << _serverConfiguration->listenAddr << ":" << _serverConfiguration->port
                                    << " encountered an error:" << std::endl;
        std::cerr << boost::diagnostic_information(exception) << std::endl;
    }
}

void LeafServer::loadConfiguration() {
    ConfigurationLoaders::LeafServerConfigurationLoader serverConfigurationLoader;

    std::cout << "LOADING CONFIG!!" << "ini_path: " << _serverIniPath << std::endl;

    _serverConfiguration = serverConfigurationLoader.load(_serverIniPath);
}


void LeafServer::run() {
    std::osyncstream(std::cout) << "Running Leaf thread: listening on "
                                << _serverConfiguration->listenAddr
                                << ":" << _serverConfiguration->port
                                << std::endl;
    _ioContext.run();
}

void LeafServer::accept() {
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

void LeafServer::registerSignalsAwaitStopCallback() {
    _signals.async_wait(
            [this](boost::system::error_code, int) {
                stop();
            });
}

void LeafServer::terminate() {
    _ioContext.stop();
}
