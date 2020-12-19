//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP
#define LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP

#include <gtest/gtest.h>
#include "server/models/leaf_server_options.hpp"

namespace Leaf::Tests {
    class LeafServerOptionsParserTest : public ::testing::Test {
    protected:
        Leaf::LeafServer::Models::LeafServerOptions *_serverOptions;

        void SetUp() override {
            Test::SetUp();
            _serverOptions = new Leaf::LeafServer::Models::LeafServerOptions;
        }

        void TearDown() override {
            Test::TearDown();
            delete _serverOptions;
            _serverOptions = nullptr;
        }

    public:
        Leaf::LeafServer::Models::LeafServerOptions *getServerOptions() {
            return _serverOptions;
        }
    };
}

#endif //LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP
