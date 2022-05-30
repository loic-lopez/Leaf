#include <gtest/gtest.h>

#include "exception/leaf_server_config_file_not_found.hpp"
#include "generated/leaf_tests_config.hpp"
#include "leaf_server/configuration_loader/leaf_server_configuration_loader.hpp"

namespace leaf::test
{

using namespace server;

TEST(LeafServerConfigurationLoaderTest, when_initialize_leaf_server_config_file_should_be_loaded)
{
  configuration_loader::LeafServerConfigurationLoader leafServerConfigurationLoader;
  std::shared_ptr<LeafServerConfiguration> leafServerConfiguration;

  EXPECT_NO_THROW({
    leafServerConfiguration = leafServerConfigurationLoader.load(config::LeafConfigRootDirectory + "/servers/http_port_80.ini");
  });

  ASSERT_TRUE(leafServerConfiguration.get() != nullptr);
}

TEST(LeafServerConfigurationLoaderTest, when_initialize_leaf_server_config_file_should_be_loaded_and_configuration_filled)
{
  configuration_loader::LeafServerConfigurationLoader leafServerConfigurationLoader;
  std::shared_ptr<LeafServerConfiguration> leafServerConfiguration;

  leafServerConfiguration = leafServerConfigurationLoader.load(config::LeafConfigRootDirectory + "/servers/http_port_80.ini");

  ASSERT_TRUE(!leafServerConfiguration->documentRootPath.empty());
  ASSERT_EQ(leafServerConfiguration->port, 80);
  ASSERT_TRUE(!leafServerConfiguration->listenAddr.empty());
}

TEST(LeafServerConfigurationLoaderTest, when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini)
{
  configuration_loader::LeafServerConfigurationLoader leafServerConfigurationLoader;

  EXPECT_THROW(leafServerConfigurationLoader.load("server.ini"), exception::LeafServerConfigFileNotFound);
}

TEST(LeafServerConfigurationLoaderTest, on_missing_section_ini_section_not_found_exception_must_be_thrown)
{
  configuration_loader::LeafServerConfigurationLoader leafServerConfigurationLoader;

  EXPECT_THROW(
    { leafServerConfigurationLoader.load(config::LeafTestsConfigDirectory + "/servers/http_port_8080_empty.ini"); },
    leaf::exception::IniSectionNotFound
  );
}

TEST(LeafServerConfigurationLoaderTest, on_missing_key_value_pair_an_exception_must_be_thrown)
{
  configuration_loader::LeafServerConfigurationLoader leafServerConfigurationLoader;

  EXPECT_THROW({ leafServerConfigurationLoader.load(config::LeafTestsConfigDirectory + "/servers/http_port_8080_with_missing_port.ini"); }, boost::wrapexcept<class leaf::exception::IniPropertyInSectionException>);
}

TEST(LeafServerConfigurationLoaderTest, on_duplicated_key_value_pair_an_exception_must_be_thrown)
{
  configuration_loader::LeafServerConfigurationLoader leafServerConfigurationLoader;

  EXPECT_THROW({ leafServerConfigurationLoader.load(config::LeafTestsConfigDirectory + "/servers/http_port_8080_with_duplicated_port.ini"); }, boost::wrapexcept<class boost::property_tree::ini_parser::ini_parser_error>);
}

}// namespace leaf::test
