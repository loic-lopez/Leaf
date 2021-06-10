//
// Created by LoicL on 17/12/2020.
//

#include <cstdlib>
#include "leaf_process_manager/leaf_process_manager.hpp"
#include "tests/leaf_server_options_parser_test.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

constexpr auto setEnv = _putenv_s;

#else

constexpr auto setEnv = [](const char *key, const char *value) {
    setenv(key, value, 0);
};

#endif

using namespace Leaf::Tests;

TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_no_params_must_throw_required_option) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());

    ASSERT_THROW(leafOptionsParser.parseCommandLineArgs(1, nullptr), boost::program_options::required_option);
}

TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_unknown_param_must_without_required_param_must_throw) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());

    std::array args = {"test", "--too"};

    ASSERT_THROW(leafOptionsParser.parseCommandLineArgs(2, args.data()), boost::program_options::required_option);
}


TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_unknown_param_must_not_throw) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());
    std::string serverConfigFileArg = "--";
    serverConfigFileArg += Leaf::CliOptions::SERVER_CONFIG_FILE;
    serverConfigFileArg += "=some_path";
    std::array args = {"test", serverConfigFileArg.c_str(), "--too"};

    ASSERT_NO_THROW(leafOptionsParser.parseCommandLineArgs(2, args.data()));
}


TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_help_option_must_return_NEED_DISPLAY_HELP) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());

    Leaf::LeafOptionsParser::Status leafOptionsParserParserStatus;
    std::array args = {"test", "--help"};
    leafOptionsParserParserStatus = leafOptionsParser.parseCommandLineArgs(2, args.data());

    ASSERT_EQ(leafOptionsParserParserStatus, Leaf::LeafOptionsParser::Status::NEED_DISPLAY_HELP);
}

TEST_F(LeafServerOptionsParserTest, parseCommandLineArgs_with_known_param_must_store_it) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());

    std::string serverConfigFileArg = "--";
    serverConfigFileArg += Leaf::CliOptions::SERVER_CONFIG_FILE;
    serverConfigFileArg += "=some_path";
    std::array args = {"test", serverConfigFileArg.c_str()};

    Leaf::LeafOptionsParser::Status leafOptionsParserParserStatus;

    ASSERT_NO_THROW(leafOptionsParserParserStatus = leafOptionsParser.parseCommandLineArgs(2, args.data()));
    ASSERT_EQ(getServerOptions()->getServerConfigFilePath(), "some_path");
    ASSERT_EQ(leafOptionsParserParserStatus, Leaf::LeafOptionsParser::Status::SUCCESS);
}

TEST_F(LeafServerOptionsParserTest, parseEnvironment_must_accept_a_good_env_var) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());

    std::string serverConfEnvName = "LEAF_SERVER_CONFIG_FILE";
    setEnv(serverConfEnvName.c_str(), "some_path");

    ASSERT_NO_THROW(leafOptionsParser.parseEnvironment());
}

TEST_F(LeafServerOptionsParserTest, parseEnvironment_must_not_crash_on_undeclared_env_var_from_environment) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());

    std::string serverConfEnvName = "LEAF_SERVER_CONFIG_FILE_FAIL";
    setEnv(serverConfEnvName.c_str(), "some_value");

    ASSERT_NO_THROW(leafOptionsParser.parseEnvironment());
}

TEST_F(LeafServerOptionsParserTest, parseEnvironment_must_not_throw_an_exception_when_not_env_var_is_provided) {
    Leaf::LeafOptionsParser leafOptionsParser(getServerOptions().get());

    ASSERT_NO_THROW(leafOptionsParser.parseEnvironment());
}


class LeafOptionsParser_Surcharged : public Leaf::LeafOptionsParser {
public:
    using Leaf::LeafOptionsParser::LeafOptionsParser;

    [[nodiscard]] std::string matchEnvironmentVariableCallable(const std::string &envVar) const {
        return this->matchEnvironmentVariable(envVar);
    };
};

TEST_F(LeafServerOptionsParserTest, matchEnvironmentVariable_must_return_a_good_variable) {
    LeafOptionsParser_Surcharged leafOptionsParser(getServerOptions().get());

    std::string matchedEnvVar = leafOptionsParser.matchEnvironmentVariableCallable(
            Leaf::EnvOptions::SERVER_CONFIG_FILE);

    ASSERT_EQ(matchedEnvVar, Leaf::EnvOptions::SERVER_CONFIG_FILE);
}

TEST_F(LeafServerOptionsParserTest, matchEnvironmentVariable_must_return_an_empty_string_on_var_not_found) {

    LeafOptionsParser_Surcharged leafOptionsParser(getServerOptions().get());

    std::string matchedEnvVar = leafOptionsParser.matchEnvironmentVariableCallable("LEAF_SOME_VAR");

    ASSERT_EQ(matchedEnvVar, "");
}


TEST_F(LeafServerOptionsParserTest, matchEnvironmentVariable_must_return_an_empty_string_on_var_not_right_prefixed) {
    LeafOptionsParser_Surcharged leafOptionsParser(getServerOptions().get());

    std::string matchedEnvVar = leafOptionsParser.matchEnvironmentVariableCallable("SOME_VAR");

    ASSERT_EQ(matchedEnvVar, "");
}




