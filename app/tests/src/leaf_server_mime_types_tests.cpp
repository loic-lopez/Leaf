#include <gtest/gtest.h>
#include "tests/leaf_server_mime_types_loader_test.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_mime_types_loader.hpp"
#include "exceptions/mime_types_config_file_not_found.hpp"

using namespace Leaf::Tests;
using namespace Leaf::LeafProcessManager::ConfigurationLoaders;

TEST_F(LeafMimeTypesLoaderTest, when_initialize_mime_types_config_file_should_be_loaded) {
    MimeTypesLoader mimeTypesLoader;

    EXPECT_NO_THROW(_mimeTypes = mimeTypesLoader.load("../conf/mime_types.ini"));
}

TEST_F(LeafMimeTypesLoaderTest, when_initialize_mime_types_config_file_should_be_loaded_and_configuration_filled) {
    MimeTypesLoader mimeTypesLoader;

    _mimeTypes = mimeTypesLoader.load("../conf/mime_types.ini");

    ASSERT_TRUE(!_mimeTypes->mimeTypes.empty());
    for (const auto &mimeType : _mimeTypes->mimeTypes) {
        ASSERT_TRUE(!mimeType.type.empty());
        ASSERT_TRUE(!mimeType.extensions.empty());
    }
}

TEST_F(LeafMimeTypesLoaderTest, when_initialize_mime_types_file_not_found_exception_must_be_thrown) {
    MimeTypesLoader mimeTypesLoader;

    EXPECT_THROW(_mimeTypes = mimeTypesLoader.load("unknown/mime_types.ini"),
                 Leaf::Exceptions::MimeTypesConfigFileNotFound);
}