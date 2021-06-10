//
// Created by LoicL on 23/01/2021.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP

#include <gtest/gtest.h>
#include "leaf_process_manager/models/leaf_process_manager_configuration.hpp"

namespace Leaf::Tests {
    class LeafProcessManagerConfigurationLoaderTest : public ::testing::Test {
    protected:
        void SetUp() override {
            Test::SetUp();
            _processManagerConfiguration = nullptr;
        }

    public:
        std::unique_ptr<Leaf::LeafProcessManager::Models::LeafProcessManagerConfiguration> _processManagerConfiguration;
    };
}

#endif //LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP
