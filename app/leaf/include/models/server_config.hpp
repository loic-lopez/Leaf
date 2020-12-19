//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIG_HPP
#define LEAF_LEAF_SERVER_CONFIG_HPP

#include <string>

namespace Leaf::Models {

    class ServerConfiguration {
    private:
        int _port;
        std::string _documentRootPath;

    };

}


#endif //LEAF_LEAF_SERVER_CONFIG_HPP
