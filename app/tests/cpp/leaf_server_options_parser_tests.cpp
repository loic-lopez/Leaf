//
// Created by LoicL on 17/12/2020.
//

#include <gtest/gtest.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <stdlib.h>

constexpr auto setEnv = _putenv_s;
#else
#include <cstdlib>
constexpr auto setEnv = [](const char *key, const char *value) {
    setenv(key, value, 0);
};
#endif

#include "server/leaf_server_options_parser.hpp"

class ServerOptionsParserTest : public ::testing::Test {
protected:
    Leaf::LeafServer::Models::ServerOptions *_serverOptions;

    void SetUp() override {
        Test::SetUp();
        _serverOptions = new Leaf::LeafServer::Models::ServerOptions;
    }

    void TearDown() override {
        Test::TearDown();
        delete _serverOptions;
        _serverOptions = nullptr;
    }

public:
    Leaf::LeafServer::Models::ServerOptions *getServerOptions() {
        return _serverOptions;
    }
};

TEST_F(ServerOptionsParserTest, test_boost_program_options_from_cli) {
    Leaf::LeafServer::ServerOptionsParser leafServerOptions(getServerOptions());

    leafServerOptions.parseCommandLineArgs(1, nullptr);
}

TEST_F(ServerOptionsParserTest, test_boost_program_options_from_cli_with_unknown_param) {
    Leaf::LeafServer::ServerOptionsParser leafServerOptions(getServerOptions());

    const char *args[] = {"--too"};
    leafServerOptions.parseCommandLineArgs(1, args);
}

TEST_F(ServerOptionsParserTest, ServerOptionsParser_must_accept_a_good_env_var) {
    Leaf::LeafServer::ServerOptionsParser leafServerOptions(getServerOptions());

    std::string serverConfEnvName = "LEAF_SERVER_CONFIG_FILE";
    setEnv(serverConfEnvName.c_str(), "some_path");

    leafServerOptions.parseEnvironment();
}

TEST_F(ServerOptionsParserTest, ServerOptionsParser_must_not_crash_on_undeclared_env_var_from_environment) {
    Leaf::LeafServer::ServerOptionsParser leafServerOptions(getServerOptions());

    std::string serverConfEnvName = "LEAF_SERVER_CONFIG_FILE_FAIL";
    //setenv(serverConfEnvName.c_str(), "", 1);
    setEnv(serverConfEnvName.c_str(), "some_value");

    leafServerOptions.parseEnvironment();
}




