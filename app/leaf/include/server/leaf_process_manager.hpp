//
// Created by LoicL on 13/12/2020.
//

#ifndef LEAF_PROCESS_MANAGER_HPP
#define LEAF_PROCESS_MANAGER_HPP

#include "server/leaf_server.hpp"
#include "leaf_server_options_parser.hpp"

namespace Leaf::LeafServer {
    class LeafProcessManager {
    private:
        LeafServer leafServer;
        ServerOptionsParser serverOptionsParser;

    public:
        void start();
    };
}


#endif //LEAF_PROCESS_MANAGER_HPP
