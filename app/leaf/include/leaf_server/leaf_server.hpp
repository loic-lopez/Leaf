//
// Created by LoicL on 23/11/2020.
//

#ifndef __LEAF_LEAF_SERVER_HPP__
#define __LEAF_LEAF_SERVER_HPP__

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
    explicit LeafServer(
      defines::Path serverIniPath, defines::Path leafLogDirectoryPath, std::size_t leafLogMaxFileSize, std::size_t leafLogMaxFiles,
      std::size_t leafLogThreadsPerLeafServer
    );
    virtual ~LeafServer() = default;

    void join();
    void stop();
    void start();

  private:
    // initializer list
    const defines::Path _serverIniPath;
    const defines::Path _leafLogDirectoryPath;
    const std::size_t _leafLogMaxFileSize;
    const std::size_t _leafLogMaxFiles;
    const std::size_t _leafLogThreadsPerLeafServer;

    /// The io_context used to perform asynchronous operations.
    boost::asio::io_context _ioContext = boost::asio::io_context(1);
    /// Acceptor used to listen for incoming connections.
    boost::asio::ip::tcp::acceptor _acceptor;

    std::shared_ptr<LeafServerConfiguration> _serverConfiguration;

    std::jthread _thread;

    void initialize();
    void loadConfiguration();
    void serve();
    void run();
    void accept();
    void initializeLoggers();
};

}// namespace leaf::server

#endif// __LEAF_LEAF_SERVER_HPP__
