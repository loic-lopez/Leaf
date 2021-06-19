//
// Created by loicl on 6/19/2021.
//

#include <chrono>
#include <thread>
#include <gtest/gtest.h>
#include "generated/leaf_tests_config.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"

using namespace Leaf::LeafServer;
using namespace std::chrono_literals;

TEST(LeafServerTests, consctruct_a_leaf_server_must_not_throw) {

    ASSERT_NO_THROW({
        LeafServer leafServer("");
    });

}

TEST(LeafServerTests, start) {

    ASSERT_NO_THROW({
        Leaf::LeafServer::LeafServer leafServer(Leaf::Tests::Config::RootDirectory + "/servers/port_8080/http_port_8080.ini");

        leafServer.start();
        std::this_thread::sleep_for(2000ms);
        leafServer.terminate();
        leafServer.join();
    });

}

