//
// Created by LoicL on 17/12/2020.
//
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
#include "tests/leaf_server_options_parser_test.hpp"

using namespace Leaf::Tests;

TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_no_params_must_throw_required_option) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());

    ASSERT_THROW(leafServerOptions.parseCommandLineArgs(1, nullptr),boost::program_options::required_option);
}

TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_unknown_param_must_without_required_param_must_throw) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());

    const char *args[] = {"test", "--too"};

    ASSERT_THROW(leafServerOptions.parseCommandLineArgs(2, args),boost::program_options::required_option);
}


TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_unknown_param_must_not_throw) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());
    std::string serverConfigFileArg = "--";
    serverConfigFileArg += Leaf::LeafServer::CliOptions::SERVER_CONFIG_FILE;
    serverConfigFileArg += "=some_path";
    const char *args[] = {"test", serverConfigFileArg.c_str(), "--too"};

    ASSERT_NO_THROW(leafServerOptions.parseCommandLineArgs(2, args));
}


TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_help_option_must_return_NEED_DISPLAY_HELP) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());

    Leaf::LeafServer::LeafServerOptionsParser::Status leafServerOptionsParserStatus;
    const char *args[] = {"test", "--help"};
    leafServerOptionsParserStatus = leafServerOptions.parseCommandLineArgs(2, args);

    ASSERT_EQ(leafServerOptionsParserStatus, Leaf::LeafServer::LeafServerOptionsParser::Status::NEED_DISPLAY_HELP);
}

TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_known_param_must_store_it) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());

    std::string serverConfigFileArg = "--";
    serverConfigFileArg += Leaf::LeafServer::CliOptions::SERVER_CONFIG_FILE;
    serverConfigFileArg += "=some_path";
    const char *args[] = {"test", serverConfigFileArg.c_str()};

    Leaf::LeafServer::LeafServerOptionsParser::Status leafServerOptionsParserStatus;

    ASSERT_NO_THROW(leafServerOptionsParserStatus = leafServerOptions.parseCommandLineArgs(2, args));
    ASSERT_EQ(getServerOptions()->getServerConfigFilePath(), "some_path");
    ASSERT_EQ(leafServerOptionsParserStatus, Leaf::LeafServer::LeafServerOptionsParser::Status::SUCCESS);
}

TEST_F(LeafServerOptionsParserTest, parseEnvironment_must_accept_a_good_env_var) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());

    std::string serverConfEnvName = "LEAF_SERVER_CONFIG_FILE";
    setEnv(serverConfEnvName.c_str(), "some_path");

    ASSERT_NO_THROW(leafServerOptions.parseEnvironment());
}

TEST_F(LeafServerOptionsParserTest, parseEnvironment_must_not_crash_on_undeclared_env_var_from_environment) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());

    std::string serverConfEnvName = "LEAF_SERVER_CONFIG_FILE_FAIL";
    setEnv(serverConfEnvName.c_str(), "some_value");

    ASSERT_NO_THROW(leafServerOptions.parseEnvironment());
}

TEST_F(LeafServerOptionsParserTest, parseEnvironment_must_not_throw_an_exception_when_not_env_var_is_provided) {
    Leaf::LeafServer::LeafServerOptionsParser leafServerOptions(getServerOptions());

    ASSERT_NO_THROW(leafServerOptions.parseEnvironment());
}


class LeafServerOptionsParser : public Leaf::LeafServer::LeafServerOptionsParser {
public:
    using Leaf::LeafServer::LeafServerOptionsParser::LeafServerOptionsParser;

    std::string matchEnvironmentVariableCallable(const std::string &envVar) {
        return this->matchEnvironmentVariable(envVar);
    };
};

TEST_F(LeafServerOptionsParserTest, matchEnvironmentVariable_must_return_a_good_variable) {

    LeafServerOptionsParser leafServerOptions(getServerOptions());

    std::string matchedEnvVar = leafServerOptions.matchEnvironmentVariableCallable(
            Leaf::LeafServer::EnvOptions::SERVER_CONFIG_FILE);

    ASSERT_EQ(matchedEnvVar, Leaf::LeafServer::EnvOptions::SERVER_CONFIG_FILE);
}

TEST_F(LeafServerOptionsParserTest, matchEnvironmentVariable_must_return_an_empty_string_on_var_not_found) {

    LeafServerOptionsParser leafServerOptions(getServerOptions());

    std::string matchedEnvVar = leafServerOptions.matchEnvironmentVariableCallable("LEAF_SOME_VAR");

    ASSERT_EQ(matchedEnvVar, "");
}


TEST_F(LeafServerOptionsParserTest, matchEnvironmentVariable_must_return_an_empty_string_on_var_not_right_prefixed) {
    LeafServerOptionsParser leafServerOptions(getServerOptions());

    std::string matchedEnvVar = leafServerOptions.matchEnvironmentVariableCallable("SOME_VAR");

    ASSERT_EQ(matchedEnvVar, "");
}




