#include <gtest/gtest.h>
#include <boost/exception/diagnostic_information.hpp>
#include "library/singleton.hpp"
#include "server/leaf_conf.hpp"
#include "exceptions/leaf_server_config_file_not_found.hpp"
#include "exceptions/error_info.hpp"

TEST(TestLeafConf, when_initialize_leaf_server_config_file_should_be_loaded) {
    Leaf::LeafServer::LeafConf &leafConf = Leaf::Singleton<Leaf::LeafServer::LeafConf>::Instance();

    leafConf.initialize("conf/leaf.ini");
}

TEST(TestLeafConf, when_initialize_leaf_conf_file_not_found_exception_must_be_thrown_when_ini) {
    Leaf::LeafServer::LeafConf &leafConf = Leaf::Singleton<Leaf::LeafServer::LeafConf>::Instance();

    EXPECT_THROW(leafConf.initialize("leaf.ini"), Leaf::Exceptions::LeafServerConfigFileNotFound);

    try {
        leafConf.initialize("leaf.ini");
    } catch (Leaf::Interfaces::IException &e) {
        std::cerr << boost::diagnostic_information(e);
    }
}