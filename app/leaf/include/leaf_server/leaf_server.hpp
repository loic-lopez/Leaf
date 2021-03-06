//
// Created by LoicL on 23/11/2020.
//

#ifndef LEAF_LEAF_SERVER_HPP
#define LEAF_LEAF_SERVER_HPP

#include <iostream>
#include <thread>
#include "leaf_server/models/leaf_server_configuration.hpp"

namespace Leaf::LeafServer {
    class LeafServer {
    private:
        std::thread _thread;
        bool _threadMustBeKilled;
        std::unique_ptr<Models::LeafServerConfiguration> _serverConfiguration;
        const std::string _serverIniPath;

    protected:
        void onStart() const;

        void loadConfiguration();

        void serve();

    public:
        explicit LeafServer(const std::string &serverIniPath);

        LeafServer(const LeafServer &leafServer);

        virtual ~LeafServer();

        void join();

        void start();
    };
}


#endif //LEAF_LEAF_SERVER_HPP
