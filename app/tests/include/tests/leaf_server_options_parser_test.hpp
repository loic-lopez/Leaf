//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP
#define LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP

#include <gtest/gtest.h>
#include "leaf_process_manager/models/leaf_process_manager_options.hpp"

namespace Leaf::Tests {
    class LeafServerOptionsParserTest : public ::testing::Test {
    private:
        std::unique_ptr<Leaf::LeafProcessManager::Models::LeafProcessManagerOptions> _processManagerOptions;

        void SetUp() override {
            Test::SetUp();
            _processManagerOptions = std::make_unique<Leaf::LeafProcessManager::Models::LeafProcessManagerOptions>();
        }

    public:
        std::unique_ptr<Leaf::LeafProcessManager::Models::LeafProcessManagerOptions> &getServerOptions() {
            return _processManagerOptions;
        }
    };
}

#endif //LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP
