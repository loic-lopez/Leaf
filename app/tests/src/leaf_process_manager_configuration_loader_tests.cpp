#include <gtest/gtest.h>
#include <boost/exception/diagnostic_information.hpp>
#include "tests/leaf_server_configuration_loader_test.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_process_manager_configuration_loader.hpp"
#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "generated/leaf_tests_config.hpp"

using namespace Leaf::Tests;
using namespace Leaf::LeafProcessManager;
using namespace Leaf::LeafProcessManager::ConfigurationLoaders;

TEST_F(LeafProcessManagerConfigurationLoaderTest, when_initialize_leaf_process_manager_config_file_should_be_loaded) {
    LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;

    EXPECT_NO_THROW(
            processManagerConfigurationLoader.load(Leaf::Tests::Config::LeafConfigRootDirectory + "/leaf.ini")
    );
}

TEST_F(LeafProcessManagerConfigurationLoaderTest,
       when_initialize_leaf_process_manager_config_file_should_be_loaded_and_configuration_filled) {
    LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;

    _processManagerConfiguration = processManagerConfigurationLoader.load(
            Leaf::Tests::Config::LeafConfigRootDirectory + "/leaf.ini");

    ASSERT_TRUE(!_processManagerConfiguration->getMimeTypesConfigFilePath().empty());
    ASSERT_TRUE(!_processManagerConfiguration->getLeafLogDirectoryPath().empty());
    ASSERT_TRUE(!_processManagerConfiguration->getServersRootPath().empty());
}

TEST_F(LeafProcessManagerConfigurationLoaderTest,
       when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini) {
    LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;

    EXPECT_THROW(processManagerConfigurationLoader.load("leaf.ini"), Leaf::Exceptions::LeafServerConfigFileNotFound);
}

TEST_F(LeafProcessManagerConfigurationLoaderTest,
     on_missing_section_ini_section_not_found_exception_must_be_thrown) {
    LeafProcessManagerConfigurationLoader processManagerConfigurationLoader;

    EXPECT_THROW(
            {
                processManagerConfigurationLoader.load(Leaf::Tests::Config::LeafTestsConfigDirectory + "/leaf.with_missing_section.ini");
            },
            Leaf::Exceptions::IniSectionNotFound
    );
}
