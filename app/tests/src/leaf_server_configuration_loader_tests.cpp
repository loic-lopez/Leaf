#include "exception/leaf_server_config_file_not_found.hpp"
#include "generated/leaf_tests_config.hpp"
#include "tests/leaf_server_configuration_loader_test.hpp"

#include <gtest/gtest.h>

namespace leaf::test
{

using namespace server;

TEST_F(LeafServerConfigurationLoaderTest, when_initialize_leaf_server_config_file_should_be_loaded)
{
  std::shared_ptr<LeafServerConfiguration> leafServerConfiguration;

  EXPECT_NO_THROW({
    leafServerConfiguration = _leafServerConfigurationLoader->load(config::LeafConfigRootDirectory + "/servers/http_port_80.ini");
  });

  ASSERT_TRUE(leafServerConfiguration.get() != nullptr);
}

TEST_F(LeafServerConfigurationLoaderTest, when_initialize_leaf_server_config_file_should_be_loaded_and_configuration_filled)
{
  std::shared_ptr<LeafServerConfiguration> leafServerConfiguration;

  leafServerConfiguration = _leafServerConfigurationLoader->load(config::LeafConfigRootDirectory + "/servers/http_port_80.ini");

  ASSERT_TRUE(!leafServerConfiguration->documentRootPath.empty());
  ASSERT_EQ(leafServerConfiguration->port, 80);
  ASSERT_TRUE(!leafServerConfiguration->listenAddr.empty());
}

TEST_F(LeafServerConfigurationLoaderTest, when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini)
{
  EXPECT_THROW(_leafServerConfigurationLoader->load("server.ini"), exception::LeafServerConfigFileNotFound);
}

TEST_F(LeafServerConfigurationLoaderTest, on_missing_section_ini_section_not_found_exception_must_be_thrown)
{
  EXPECT_THROW(
    { _leafServerConfigurationLoader->load(config::LeafTestsConfigDirectory + "/servers/http_port_8080_empty.ini"); },
    leaf::exception::IniSectionNotFound
  );
}

TEST_F(LeafServerConfigurationLoaderTest, on_missing_key_value_pair_an_exception_must_be_thrown)
{
  EXPECT_THROW({ _leafServerConfigurationLoader->load(config::LeafTestsConfigDirectory + "/servers/http_port_8080_with_missing_port.ini"); }, boost::wrapexcept<class leaf::exception::IniPropertyInSectionException>);
}

TEST_F(LeafServerConfigurationLoaderTest, on_duplicated_key_value_pair_an_exception_must_be_thrown)
{
  EXPECT_THROW({ _leafServerConfigurationLoader->load(config::LeafTestsConfigDirectory + "/servers/http_port_8080_with_duplicated_port.ini"); }, boost::wrapexcept<class boost::property_tree::ini_parser::ini_parser_error>);
}

}// namespace leaf::test
