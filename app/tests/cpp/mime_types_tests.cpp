#include <gtest/gtest.h>
#include "library/singleton.hpp"
#include "server/mime_types.hpp"
#include "exceptions/mime_types_config_file_not_found.hpp"

TEST(TestMimeTypes, when_initialize_mime_types_config_file_should_be_loaded) {
    Leaf::LeafServer::MimeTypes &mimeTypes = Leaf::Singleton<Leaf::LeafServer::MimeTypes>::Instance();

    mimeTypes.initialize("E:/Projects/Leaf/cmake-build-debug/conf/leaf.ini");
}

TEST(TestMimeTypes, when_initialize_mime_types_file_not_found_exception_must_be_thrown) {
    Leaf::LeafServer::MimeTypes &mimeTypes = Leaf::Singleton<Leaf::LeafServer::MimeTypes>::Instance();

    EXPECT_THROW(mimeTypes.initialize("leaf.ini"), Leaf::Exceptions::MimeTypesConfigFileNotFound);
}