//
// Created by loicl on 8/1/2022.
//

#ifndef __LEAF_TESTS_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP__
#define __LEAF_TESTS_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP__

#include "log/logger_factory.hpp"
#include "leaf_server/configuration_loader/leaf_server_configuration_loader.hpp"

#include <gtest/gtest.h>

#include <memory>

namespace leaf::test
{
  class LeafServerConfigurationLoaderTest : public ::testing::Test
  {
      void SetUp() override
      {
        Test::SetUp();
        log::LoggerFactory::InitializeFactory();
        _leafServerConfigurationLoader = std::make_unique<server::configuration_loader::LeafServerConfigurationLoader>();
      }

      void TearDown() override {
        log::LoggerFactory::ShutdownGlobalThreadPool();
        Test::TearDown();
      }

    public:
      std::unique_ptr<server::configuration_loader::LeafServerConfigurationLoader> _leafServerConfigurationLoader;
  };
}

#endif// __LEAF_TESTS_LEAF_SERVER_CONFIGURATION_LOADER_TEST_HPP__
