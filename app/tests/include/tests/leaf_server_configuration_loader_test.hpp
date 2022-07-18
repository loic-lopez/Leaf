//
// Created by LoicL on 23/01/2021.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP

#include "leaf_process_manager/leaf_process_manager_configuration.hpp"
#include "log/logger_factory.hpp"

#include <gtest/gtest.h>

namespace leaf::test
{
class LeafProcessManagerConfigurationLoaderTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
      Test::SetUp();
      log::LoggerFactory::InitializeFactory();
      _processManagerConfiguration = nullptr;
    }

  public:
    std::unique_ptr<leaf::process_manager::LeafProcessManagerConfiguration> _processManagerConfiguration;
};
}// namespace leaf::test

#endif// LEAF_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP
