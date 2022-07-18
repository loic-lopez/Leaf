//
// Created by LoicL on 23/11/2020.
//

#ifndef LEAF_LEAF_SERVER_HPP
#define LEAF_LEAF_SERVER_HPP

#include "leaf_server/leaf_server_configuration.hpp"
#include "log/logger_interface.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>

#include <iostream>
#include <thread>

namespace leaf::server
{
class LeafServer : public log::LoggerInterface
{
  public:
    LeafServer(const LeafServer &leafServer) = delete;
    explicit LeafServer(std::string serverIniPath, std::string leafLogDirectoryPath, std::size_t leafLogMaxFileSize,
                        std::size_t leafLogMaxFiles);
    virtual ~LeafServer() = default;

    void join();
    void terminate();
    void start();

  private:
    // initializer list
    const std::string _serverIniPath;
    const std::string _leafLogDirectoryPath;
    const std::size_t _leafLogMaxFileSize;
    const std::size_t _leafLogMaxFiles;

    /// The io_context used to perform asynchronous operations.
    boost::asio::io_context _ioContext = boost::asio::io_context(1);
    /// The signal_set is used to register for process termination notifications.
    boost::asio::signal_set _signals;
    /// Acceptor used to listen for incoming connections.
    boost::asio::ip::tcp::acceptor _acceptor;

    std::shared_ptr<LeafServerConfiguration> _serverConfiguration;

    std::jthread _thread;

    void initialize();
    void loadConfiguration();
    void serve();
    void run();
    void registerSignalsAwaitStopCallback();
    void accept();
    void stop();
};

}// namespace leaf::server

#endif// LEAF_LEAF_SERVER_HPP
