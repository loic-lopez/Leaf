//
// Created by LoicL on 28/02/2021.
//

#include "leaf_server/leaf_server_configuration.hpp"

namespace leaf::server
{

LeafServerConfiguration::LeafServerConfiguration(const int port, std::string documentRootPath, std::string listenAddr)
    : port(port), documentRootPath(std::move(documentRootPath)), listenAddr(std::move(listenAddr))
{
}

}// namespace leaf::server
