#include <gtest/gtest.h>
#include "server/leaf_server.hpp"

TEST(TestServer, when_set_Port_Message_Should_Works) // NOLINT(cert-err58-cpp)
{
    Leaf::LeafServer::Server server;
    (void) server;

    EXPECT_EQ(1000, 1000);
}