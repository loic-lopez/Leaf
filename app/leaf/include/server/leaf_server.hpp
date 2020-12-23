//
// Created by LoicL on 23/11/2020.
//

#ifndef LEAF_SERVER_HPP
#define LEAF_SERVER_HPP

#include <iostream>
#include <thread>
#include "models/server_configuration.hpp"

namespace Leaf::LeafServer {
    class LeafServer {
    private:
        std::thread _thread;
        bool _threadMustBeKilled;
        Models::ServerConfiguration *_serverConfiguration;

    protected:
        void onStart() const;

        LeafServer *loadConfiguration(const std::string &serverIniPath);

        void serve();

    public:
        explicit LeafServer();

        virtual ~LeafServer();

        void join();

        void start();
    };
}


#endif //LEAF_SERVER_HPP
