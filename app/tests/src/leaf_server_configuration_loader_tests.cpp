#include <gtest/gtest.h>
#include <boost/exception/diagnostic_information.hpp>
#include "tests/leaf_server_configuration_loader_test.hpp"
#include "server/configuration_loaders/leaf_server_configuration_loader.hpp"
#include "exceptions/leaf_server_config_file_not_found.hpp"

using namespace Leaf::Tests;
using namespace Leaf::LeafServer;
using namespace Leaf::LeafServer::ConfigurationLoaders;

TEST_F(LeafServerConfigurationLoaderTest, when_initialize_leaf_server_config_file_should_be_loaded) {
    LeafServerConfigurationLoader serverConfigurationLoader;

    EXPECT_NO_THROW(
            _leafServerConfiguration = serverConfigurationLoader.load("../conf/leaf.ini")
    );
}

TEST_F(LeafServerConfigurationLoaderTest,
       when_initialize_leaf_server_config_file_should_be_loaded_and_configuration_filled) {
    LeafServerConfigurationLoader serverConfigurationLoader;

    _leafServerConfiguration = serverConfigurationLoader.load("../conf/leaf.ini");

    ASSERT_TRUE(!_leafServerConfiguration->mimeTypesConfigFile.empty());
    ASSERT_TRUE(!_leafServerConfiguration->leafConfigurationDirectory.empty());
    ASSERT_TRUE(!_leafServerConfiguration->leafLogDirectory.empty());
    ASSERT_TRUE(!_leafServerConfiguration->serversRootPath.empty());
}

TEST_F(LeafServerConfigurationLoaderTest, when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini) {
    LeafServerConfigurationLoader serverConfigurationLoader;

    EXPECT_THROW(serverConfigurationLoader.load("leaf.ini"), Leaf::Exceptions::LeafServerConfigFileNotFound);
}