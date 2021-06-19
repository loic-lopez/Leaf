#include <gtest/gtest.h>
#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "generated/leaf_tests_config.hpp"
#include "leaf_server/configuration_loaders/leaf_server_configuration_loader.hpp"

using namespace Leaf::LeafServer;

TEST(LeafServerConfigurationLoaderTest, when_initialize_leaf_server_config_file_should_be_loaded) {
    ConfigurationLoaders::LeafServerConfigurationLoader leafServerConfigurationLoader;
    std::shared_ptr<Models::LeafServerConfiguration> leafServerConfiguration;

    EXPECT_NO_THROW({
        leafServerConfiguration = leafServerConfigurationLoader.load(Leaf::Tests::Config::RootDirectory + "/servers/http_port_80.ini");
    });

    ASSERT_TRUE(leafServerConfiguration.get() != nullptr);
}

TEST(LeafServerConfigurationLoaderTest,
     when_initialize_leaf_server_config_file_should_be_loaded_and_configuration_filled) {
    ConfigurationLoaders::LeafServerConfigurationLoader leafServerConfigurationLoader;
    std::shared_ptr<Models::LeafServerConfiguration> leafServerConfiguration;

    leafServerConfiguration = leafServerConfigurationLoader.load(Leaf::Tests::Config::RootDirectory + "/servers/http_port_80.ini");

    ASSERT_TRUE(!leafServerConfiguration->documentRootPath.empty());
    ASSERT_EQ(leafServerConfiguration->port, 80);
    ASSERT_TRUE(!leafServerConfiguration->listenAddr.empty());
}

TEST(LeafServerConfigurationLoaderTest,
     when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini) {
    ConfigurationLoaders::LeafServerConfigurationLoader leafServerConfigurationLoader;

    EXPECT_THROW(leafServerConfigurationLoader.load("server.ini"), Leaf::Exceptions::LeafServerConfigFileNotFound);
}