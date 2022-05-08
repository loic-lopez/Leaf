//
// Created by LoicL on 23/11/2020.
//

#ifndef LEAF_LEAF_SERVER_HPP
#define LEAF_LEAF_SERVER_HPP

#include <iostream>
#include <thread>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>

#include "leaf_server_configuration.hpp"

namespace leaf::server
{
class LeafServer
{
 private:// initializer list
  std::jthread _thread;
  const std::string _serverIniPath;
  /// The io_context used to perform asynchronous operations.
  boost::asio::io_context _ioContext = boost::asio::io_context(1);
  /// The signal_set is used to register for process termination notifications.
  boost::asio::signal_set _signals;
  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor _acceptor;

 public:
  LeafServer(const LeafServer &leafServer) = delete;
  explicit LeafServer(std::string serverIniPath);

  void join();
  void terminate();
  void start();

 private:
  std::shared_ptr<LeafServerConfiguration> _serverConfiguration;

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
