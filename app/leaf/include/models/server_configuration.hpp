//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_SERVER_CONFIGURATION_HPP
#define LEAF_SERVER_CONFIGURATION_HPP

#include <string>

namespace Leaf::Models {

    class ServerConfiguration {
    public:
        const int port;
        const std::string documentRootPath;
        const std::string listenAddr;

    };

}


#endif //LEAF_SERVER_CONFIGURATION_HPP
