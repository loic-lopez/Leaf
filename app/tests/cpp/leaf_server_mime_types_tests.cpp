#include <gtest/gtest.h>
#include "library/singleton.hpp"
#include "server/configuration_loaders/leaf_mime_types_loader.hpp"
#include "exceptions/mime_types_config_file_not_found.hpp"

using namespace Leaf::LeafServer::ConfigurationLoaders;

TEST(TestMimeTypes, when_initialize_mime_types_config_file_should_be_loaded) {
    MimeTypes mimeTypesLoader;

    mimeTypesLoader.load("conf/mime_types.ini");
}

TEST(TestMimeTypes, when_initialize_mime_types_file_not_found_exception_must_be_thrown) {
    MimeTypes mimeTypesLoader;

    EXPECT_THROW(mimeTypesLoader.load("unknown/mime_types.ini"), Leaf::Exceptions::MimeTypesConfigFileNotFound);
}