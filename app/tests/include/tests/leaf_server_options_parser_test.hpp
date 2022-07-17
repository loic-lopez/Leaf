//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP
#define LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP

#include "leaf_process_manager/leaf_process_manager_options.hpp"

#include <gtest/gtest.h>

namespace leaf::test
{
class LeafServerOptionsParserTest : public ::testing::Test
{
  private:
    std::unique_ptr<process_manager::LeafProcessManagerOptions> _processManagerOptions;

    void SetUp() override
    {
      Test::SetUp();
      _processManagerOptions = std::make_unique<process_manager::LeafProcessManagerOptions>();
    }

  public:
    std::unique_ptr<process_manager::LeafProcessManagerOptions> &getServerOptions() { return _processManagerOptions; }
};
}// namespace leaf::test

#endif// LEAF_LEAFSERVEROPTIONSPARSERTEST_HPP
