//
// Created by LoicL on 23/11/2020.
//

#ifndef LEAF_LEAF_SERVER_HPP
#define LEAF_LEAF_SERVER_HPP

#include <iostream>
#include <thread>
#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "leaf_server/models/leaf_server_configuration.hpp"

namespace Leaf::LeafServer {
    class LeafServer {
    private: // initializer list
        std::jthread _thread;
        bool _threadMustBeKilled = false;
        const std::string _serverIniPath;

        /// The io_context used to perform asynchronous operations.
        boost::asio::io_context _ioContext = boost::asio::io_context(1);

        /// The signal_set is used to register for process termination notifications.
        boost::asio::signal_set _signals;

        /// Acceptor used to listen for incoming connections.
        boost::asio::ip::tcp::acceptor _acceptor;

    public:
        explicit LeafServer(std::string serverIniPath);

        LeafServer(const LeafServer &leafServer) = delete;

        void join();

        void start();

    private:
        std::shared_ptr<Models::LeafServerConfiguration> _serverConfiguration;

        void initialize();

        void loadConfiguration();

        void serve();

        void run();

        void registerSignalsAwaitStopCallback();

        void accept();

        void stop();
    };


}


#endif //LEAF_LEAF_SERVER_HPP
