//
// Created by loicl on 6/19/2021.
//

#include <chrono>
#include <thread>
#include <gtest/gtest.h>
#include "generated/leaf_tests_config.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.hpp"
#include "leaf_server/leaf_server.hpp"

#if defined(BOOST_OS_WINDOWS)
#define ENABLE_LEAF_SERVER_LAUNCH false
#else
#define ENABLE_LEAF_SERVER_LAUNCH true
#endif

using namespace Leaf::LeafServer;
using namespace std::chrono_literals;

TEST(LeafServerTests, construct_a_leaf_server_must_not_throw) {

    ASSERT_NO_THROW({
        LeafServer leafServer("");
    });

}

TEST(LeafServerTests, test_for_server_thread_bind) {

    ASSERT_NO_THROW({
        Leaf::LeafServer::LeafServer leafServer(Leaf::Tests::Config::LeafConfigRootDirectory + "/servers/port_8080/http_port_8080.ini");

        if (ENABLE_LEAF_SERVER_LAUNCH) { // this part of the tests are not working on windows ???
            leafServer.start();
            std::this_thread::sleep_for(5000ms);
        }
        leafServer.terminate();
        leafServer.join();
    });

}

