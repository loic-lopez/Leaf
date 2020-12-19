//
// Created by LoicL on 12/12/2020.
//

#include <iostream>
#include <boost/program_options/parsers.hpp>
#include <boost/algorithm/string.hpp>
#include "server/leaf_build.hpp"
#include "server/leaf_server_options_parser.hpp"

using namespace Leaf::LeafServer;

LeafServerOptionsParser::LeafServerOptionsParser(Models::LeafServerOptions *serverOptions) :
        _notifier(this),
        _serverCliRequiredOptionsDescription("Required available options"),
        _serverCliOptionalOptionsDescription("Optional available options"),
        _leafServerOptions(serverOptions) {

    _serverConfigFileValue = boost::program_options::value<std::string>()
            ->notifier(_notifier.makeServerConfigFileNotifier());

    _serverCliRequiredOptionsDescription.add_options()
            (CliOptions::SERVER_CONFIG_FILE,
             _serverConfigFileValue,
             "set the config .ini file path for the server.");

    _serverCliOptionalOptionsDescription.add_options()
            (CliOptions::HELP, "display this help message");

    _serverEnvOptionsDescription.add_options()
            (EnvOptions::SERVER_CONFIG_FILE,
                    boost::program_options::value<std::string>()->notifier(_notifier.makeServerConfigFileNotifier()));

    _callbacksThatTriggersHelp[CliOptions::HELP] = CallbackReceiver{
            .optionVerifier = [](const std::string &option,
                                 const boost::program_options::variables_map &commandLineArgs) -> bool {
                return commandLineArgs.contains(option);
            },
            .statusWhenOptionVerifierMatched = Status::NEED_DISPLAY_HELP
    };
}

LeafServerOptionsParser::Status LeafServerOptionsParser::parseCommandLineArgs(const int ac, const char **av) {
    boost::program_options::variables_map optionalCommandLineArgs;

    boost::program_options::basic_parsed_options<char> optionalOptions =
            boost::program_options::command_line_parser(ac, av)
                    .options(_serverCliOptionalOptionsDescription)
                    .allow_unregistered().run();

    boost::program_options::store(optionalOptions, optionalCommandLineArgs);
    boost::program_options::notify(optionalCommandLineArgs);

    for (const auto &callback : this->_callbacksThatTriggersHelp) {
        if (callback.second.optionVerifier(callback.first, optionalCommandLineArgs)) {
            return callback.second.statusWhenOptionVerifierMatched;
        }
    }

    if (_leafServerOptions->getServerConfigFilePath().empty()) { // make field required if not already set by the ENV
        _serverConfigFileValue->required();
    }

    // reset
    boost::program_options::variables_map requiredCommandLineArgs;

    boost::program_options::basic_parsed_options<char> requiredOptions =
            boost::program_options::command_line_parser(ac, av)
                    .options(_serverCliRequiredOptionsDescription)
                    .allow_unregistered().run();

    boost::program_options::store(requiredOptions, requiredCommandLineArgs);
    boost::program_options::notify(requiredCommandLineArgs);

    return Status::SUCCESS;
}

void LeafServerOptionsParser::parseEnvironment() {
    boost::program_options::variables_map envVars;

    boost::program_options::store(
            boost::program_options::parse_environment(
                    _serverEnvOptionsDescription,
                    [this](const std::string &envVar) -> std::string {
                        return this->matchEnvironmentVariable(envVar);
                    }),
            envVars
    );
    boost::program_options::notify(envVars);
}

std::string LeafServerOptionsParser::matchEnvironmentVariable(const std::string &envVar) {
    if (!boost::algorithm::contains(envVar, EnvOptions::ENV_PREFIX)) return "";

    bool matched = std::any_of(
            this->_serverEnvOptionsDescription.options().cbegin(),
            this->_serverEnvOptionsDescription.options().cend(),
            [envVar](const boost::shared_ptr<boost::program_options::option_description> &opt) {
                return envVar == opt->long_name();
            });
    return matched ? envVar : "";
}

void LeafServerOptionsParser::displayHelp() {
    std::cout << "Leaf: " << LeafVersion
              << ", build type: " << LeafBuildType
              << ", build date: " << LeafBuildDate << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "Required options: [--option=value]" << std::endl;
    std::cout << "Optional options: [--option]" << std::endl << std::endl;
    std::cout << _serverCliRequiredOptionsDescription << std::endl;
    std::cout << _serverCliOptionalOptionsDescription << std::endl;
}

std::function<void(const std::string &)> LeafServerOptionsParser::Notifier::makeServerConfigFileNotifier() {
    return [this](const std::string &value) -> void {
        this->_leafServerOptionsParser->_leafServerOptions->setServerConfigFilePath(value);
    };
}

LeafServerOptionsParser::Notifier::Notifier(LeafServerOptionsParser *const leafServerOptionsParser)
        : _leafServerOptionsParser(leafServerOptionsParser) {}
