#include "exception/mime_types_config_file_not_found.hpp"
#include "generated/leaf_tests_config.hpp"
#include "leaf_process_manager/configuration_loader/leaf_mime_types_loader.hpp"
#include "tests/leaf_server_mime_types_loader_test.hpp"

#include <gtest/gtest.h>

namespace leaf::test
{

using namespace process_manager::configuration_loader;

TEST_F(LeafMimeTypesLoaderTest, when_initialize_mime_types_config_file_should_be_loaded)
{
  MimeTypesLoader mimeTypesLoader;

  EXPECT_NO_THROW(_mimeTypes = mimeTypesLoader.load(config::LeafConfigRootDirectory + "/mime_types.ini"));
}

TEST_F(LeafMimeTypesLoaderTest, when_initialize_mime_types_config_file_should_be_loaded_and_configuration_filled)
{
  MimeTypesLoader mimeTypesLoader;

  _mimeTypes = mimeTypesLoader.load(config::LeafConfigRootDirectory + "/mime_types.ini");

  ASSERT_TRUE(!_mimeTypes->mimeTypes.empty());
  for (const auto &mimeType : _mimeTypes->mimeTypes)
  {
    ASSERT_TRUE(!mimeType.type.empty());
    ASSERT_TRUE(!mimeType.extensions.empty());
  }
}

TEST_F(LeafMimeTypesLoaderTest, when_initialize_mime_types_file_not_found_exception_must_be_thrown)
{
  MimeTypesLoader mimeTypesLoader;

  EXPECT_THROW(_mimeTypes = mimeTypesLoader.load("unknown/mime_types.ini"), exception::MimeTypesConfigFileNotFound);
}

TEST_F(LeafMimeTypesLoaderTest, on_missing_section_ini_section_not_found_exception_must_be_thrown)
{
  MimeTypesLoader mimeTypesLoader;

  EXPECT_THROW({ mimeTypesLoader.load(config::LeafTestsConfigDirectory + "/mime_types_empty.ini"); }, exception::IniSectionNotFound);
}

}// namespace leaf::test
