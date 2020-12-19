//
// Created by LoicL on 23/11/2020.
//

#ifndef LEAF_SERVER_HPP
#define LEAF_SERVER_HPP

#include <iostream>
#include <thread>
#include "models/server_config.hpp"

namespace Leaf::LeafServer {
    class LeafServer {
    private:
        std::thread _thread;
        bool _threadMustBeKilled;

    protected:
        void serve();

    public:
        explicit LeafServer();

        virtual ~LeafServer();

        void onStart() const;

        LeafServer &initialize(const Leaf::Models::ServerConfiguration &serverConfiguration);

        void join();

        void start();
    };
}


#endif //LEAF_SERVER_HPP
