//
// Created by LoicL on 19/12/2020.
//

#ifndef __LEAF_LEAF_SERVER_OPTIONS_PARSER_TEST_HPP__
#define __LEAF_LEAF_SERVER_OPTIONS_PARSER_TEST_HPP__

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

#endif// __LEAF_LEAF_SERVER_OPTIONS_PARSER_TEST_HPP__
