#include <gtest/gtest.h>
#include <boost/exception/diagnostic_information.hpp>
#include "tests/leaf_server_configuration_loader_test.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.hpp"
#include "exceptions/leaf_server_config_file_not_found.hpp"

using namespace Leaf::Tests;
using namespace Leaf::LeafProcessManager;
using namespace Leaf::LeafProcessManager::ConfigurationLoaders;

TEST_F(LeafProcessManagerConfigurationLoaderTest, when_initialize_leaf_server_config_file_should_be_loaded) {
    LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;

    EXPECT_NO_THROW(
            _processManagerConfiguration = processManagerConfigurationLoader.load("../conf/leaf.ini")
    );
}

TEST_F(LeafProcessManagerConfigurationLoaderTest,
       when_initialize_leaf_server_config_file_should_be_loaded_and_configuration_filled) {
    LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;

    _processManagerConfiguration = processManagerConfigurationLoader.load("../conf/leaf.ini");

    ASSERT_TRUE(!_processManagerConfiguration->mimeTypesConfigFile.empty());
    ASSERT_TRUE(!_processManagerConfiguration->leafConfigurationDirectory.empty());
    ASSERT_TRUE(!_processManagerConfiguration->leafLogDirectory.empty());
    ASSERT_TRUE(!_processManagerConfiguration->serversRootPath.empty());
}

TEST_F(LeafProcessManagerConfigurationLoaderTest,
       when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini) {
    LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;

    EXPECT_THROW(processManagerConfigurationLoader.load("leaf.ini"), Leaf::Exceptions::LeafServerConfigFileNotFound);
}