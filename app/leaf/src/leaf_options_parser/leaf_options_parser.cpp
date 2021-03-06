//
// Created by LoicL on 12/12/2020.
//

#include <iostream>
#include <boost/program_options/parsers.hpp>
#include <boost/algorithm/string.hpp>
#include "utils/utils.hpp"
#include "leaf_options_parser/leaf_options_parser.hpp"

using namespace Leaf;
using namespace Leaf::LeafProcessManager;

LeafOptionsParser::LeafOptionsParser(Models::LeafProcessManagerOptions *serverOptions) :
        _notifier(serverOptions),
        _serverCliRequiredOptionsDescription("Required options"),
        _serverCliOptionalOptionsDescription("Optional options"),
        _leafProcessManagerOptions(serverOptions) {

    _serverConfigFileValue = boost::program_options::value<std::string>()
            ->notifier(_notifier.makeServerConfigFileNotifier());

    _serverCliRequiredOptionsDescription.add_options()
            (CliOptions::SERVER_CONFIG_FILE,
             _serverConfigFileValue,
             "set the config .ini file path for the leaf_server.");

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

LeafOptionsParser::Status LeafOptionsParser::parseCommandLineArgs(const int ac, const char **av) {
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

    if (_leafProcessManagerOptions->getServerConfigFilePath().empty()) { // make field required if not already set by the ENV
        _serverConfigFileValue->required();
    }

    boost::program_options::variables_map requiredCommandLineArgs;

    boost::program_options::basic_parsed_options<char> requiredOptions =
            boost::program_options::command_line_parser(ac, av)
                    .options(_serverCliRequiredOptionsDescription)
                    .allow_unregistered().run();

    boost::program_options::store(requiredOptions, requiredCommandLineArgs);
    boost::program_options::notify(requiredCommandLineArgs);

    return Status::SUCCESS;
}

void LeafOptionsParser::parseEnvironment() {
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

std::string LeafOptionsParser::matchEnvironmentVariable(const std::string &envVar) {
    if (!boost::algorithm::contains(envVar, EnvOptions::ENV_PREFIX)) return "";

    bool matched = std::any_of(
            this->_serverEnvOptionsDescription.options().cbegin(),
            this->_serverEnvOptionsDescription.options().cend(),
            [envVar](const boost::shared_ptr<boost::program_options::option_description> &opt) {
                return envVar == opt->long_name();
            });
    return matched ? envVar : "";
}

void LeafOptionsParser::displayHelp() {
    std::cout << "Leaf: " << Utils::BuildInfo() << std::endl;
    std::cout << "Usage: [--option=value] [--option]" << std::endl << std::endl;
    std::cout << _serverCliRequiredOptionsDescription << std::endl;
    std::cout << _serverCliOptionalOptionsDescription << std::endl;
}

std::function<void(const std::string &)> LeafOptionsParser::Notifier::makeServerConfigFileNotifier() {
    return [this](const std::string &value) -> void {
        this->_leafServerOptions->setServerConfigFilePath(value);
    };
}

LeafOptionsParser::Notifier::Notifier(Models::LeafProcessManagerOptions *const leafServerOptions)
        : _leafServerOptions(leafServerOptions) {}
