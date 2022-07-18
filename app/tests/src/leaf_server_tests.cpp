//
// Created by loicl on 6/19/2021.
//

#include "generated/leaf_tests_config.hpp"
#include "leaf_process_manager/configuration_loader/leaf_process_manager_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"

#include "log/logger_factory.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

namespace leaf::test
{

using namespace std::chrono_literals;
using namespace server;

TEST(LeafServerTests, construct_a_leaf_server_must_not_throw)
{
  log::LoggerFactory::InitializeFactory();
  ASSERT_NO_THROW({ LeafServer leafServer("", "log", 1, 1); });
}

TEST(LeafServerTests, test_for_server_thread_bind)
{
  log::LoggerFactory::InitializeFactory();
  ASSERT_NO_THROW({
    LeafServer leafServer(config::LeafConfigRootDirectory + "/servers/port_8080/http_port_8080.ini", "log", 1, 1);

    {
      leafServer.start();
      std::this_thread::sleep_for(5000ms);
    }
    leafServer.terminate();
    leafServer.join();
  });
}

}// namespace leaf::test
