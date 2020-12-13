//
// Created by LoicL on 23/01/2021.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP

#include <gtest/gtest.h>
#include "server/models/leaf_server_configuration.hpp"

namespace Leaf::Tests {
    class LeafServerConfigurationLoaderTest : public ::testing::Test {
    protected:
        void SetUp() override {
            Test::SetUp();
            _leafServerConfiguration = nullptr;
        }

        void TearDown() override {
            Test::TearDown();
            if (_leafServerConfiguration != nullptr) {
                delete _leafServerConfiguration;
            }
        }

    public:
        Leaf::LeafServer::Models::LeafServerConfiguration *_leafServerConfiguration;
    };
}

#endif //LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP
