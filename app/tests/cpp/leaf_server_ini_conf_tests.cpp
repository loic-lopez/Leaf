#include <gtest/gtest.h>
#include <boost/exception/diagnostic_information.hpp>
#include "server/configuration_loaders/leaf_server_configuration_loader.hpp"
#include "exceptions/leaf_server_config_file_not_found.hpp"

using namespace Leaf::LeafServer::ConfigurationLoaders;

TEST(TestLeafConf, when_initialize_leaf_server_config_file_should_be_loaded) {
    ServerConfiguration leafConf;

    leafConf.load("conf/leaf.ini");
}

TEST(TestLeafConf, when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini) {
    ServerConfiguration leafConf;

    EXPECT_THROW(leafConf.load("leaf.ini"), Leaf::Exceptions::LeafServerConfigFileNotFound);

/*    try {
        leafConf.load("leaf.ini");
    } catch (Leaf::Interfaces::IException &e) {
        std::cerr << boost::diagnostic_information(e);
    }*/
}