//
// Created by LoicL on 23/11/2020.
//

#ifndef LEAF_SERVER_HPP
#define LEAF_SERVER_HPP

#include <iostream>
#include "server/models/leaf_server_options.hpp"

namespace Leaf::LeafServer {
    class LeafServer {
    private:


    public:
        void onStart() const;

        void initialize(const Models::ServerOptions &leafServerOptions);
    };
}


#endif //LEAF_SERVER_HPP
