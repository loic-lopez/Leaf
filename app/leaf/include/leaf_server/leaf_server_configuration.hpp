//
// Created by LoicL on 19/12/2020.
//

#ifndef __LEAF_LEAF_SERVER_CONFIGURATION_HPP__
#define __LEAF_LEAF_SERVER_CONFIGURATION_HPP__

#include <string>

namespace leaf::server
{

class LeafServerConfiguration
{
  public:
    const int port;
    const std::string documentRootPath;
    const std::string listenAddr;

    explicit LeafServerConfiguration(int port, std::string documentRootPath, std::string listenAddr);
};

}// namespace leaf::server

#endif// __LEAF_LEAF_SERVER_CONFIGURATION_HPP__
