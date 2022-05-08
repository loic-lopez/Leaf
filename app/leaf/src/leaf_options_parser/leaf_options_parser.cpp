//
// Created by LoicL on 12/12/2020.
//

#include "leaf_options_parser/leaf_options_parser.hpp"
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/program_options/parsers.hpp>

#include "utils/utils.hpp"

namespace leaf
{
LeafOptionsParser::LeafOptionsParser(process_manager::LeafProcessManagerOptions *const serverOptions)
    : _notifier(serverOptions), _leafProcessManagerOptions(serverOptions)
{
  _configFileValue = boost::program_options::value<std::string>()->notifier(_notifier.makeServerConfigFileNotifier());

  _cliRequiredOptionsDescription.add_options()(cli_options::SERVER_CONFIG_FILE, _configFileValue,
                                               "set the config .ini file path for the leaf server.");

  _cliOptionalOptionsDescription.add_options()(cli_options::HELP, "display this help message");

  _envOptionsDescription.add_options()(env_options::SERVER_CONFIG_FILE,
                                       boost::program_options::value<std::string>()->notifier(_notifier.makeServerConfigFileNotifier()));

  _callbacksThatTriggersHelp[cli_options::HELP] =
    CallbackReceiver {.optionVerifier = [](const std::string &option, const boost::program_options::variables_map &commandLineArgs) -> bool
                      { return commandLineArgs.contains(option); },
                      .statusWhenOptionVerifierMatched = Status::NEED_DISPLAY_HELP};
}

LeafOptionsParser::Status LeafOptionsParser::parseCommandLineArgs(const int ac, const char **av)
{
  boost::program_options::variables_map optionalCommandLineArgs;

  boost::program_options::basic_parsed_options<char> optionalOptions =
    boost::program_options::command_line_parser(ac, av).options(_cliOptionalOptionsDescription).allow_unregistered().run();

  boost::program_options::store(optionalOptions, optionalCommandLineArgs);
  boost::program_options::notify(optionalCommandLineArgs);

  for (const auto &[first, second] : this->_callbacksThatTriggersHelp)
  {
    if (second.optionVerifier(first, optionalCommandLineArgs)) { return second.statusWhenOptionVerifierMatched; }
  }

  if (_leafProcessManagerOptions->getServerConfigFilePath().empty())
  {// make field required if not already set by the ENV
    _configFileValue->required();
  }

  boost::program_options::variables_map requiredCommandLineArgs;

  boost::program_options::basic_parsed_options<char> requiredOptions =
    boost::program_options::command_line_parser(ac, av).options(_cliRequiredOptionsDescription).allow_unregistered().run();

  boost::program_options::store(requiredOptions, requiredCommandLineArgs);
  boost::program_options::notify(requiredCommandLineArgs);

  return Status::SUCCESS;
}

void LeafOptionsParser::parseEnvironment() const
{
  boost::program_options::variables_map envVars;

  boost::program_options::store(
    boost::program_options::parse_environment(
      _envOptionsDescription, [this](const std::string &envVar) -> std::string { return this->matchEnvironmentVariable(envVar); }),
    envVars);
  boost::program_options::notify(envVars);
}

std::string LeafOptionsParser::matchEnvironmentVariable(const std::string &envVar) const
{
  if (!boost::algorithm::contains(envVar, env_options::ENV_PREFIX)) return "";

  bool matched = std::ranges::any_of(this->_envOptionsDescription.options().cbegin(), this->_envOptionsDescription.options().cend(),
                                     [envVar](const boost::shared_ptr<boost::program_options::option_description> &opt) -> bool
                                     { return envVar == opt->long_name(); });
  return matched ? envVar : "";
}

void LeafOptionsParser::displayHelp()
{
  std::cout << "Leaf: " << utils::BuildInfo() << std::endl;
  std::cout << "Usage: [--option=value] [--option]" << std::endl << std::endl;
  std::cout << _cliRequiredOptionsDescription << std::endl;
  std::cout << _cliOptionalOptionsDescription << std::endl;
}

std::function<void(const std::string &)> LeafOptionsParser::Notifier::makeServerConfigFileNotifier()
{
  return [this](const std::string &value) -> void { this->_leafProcessManagerOptions->setServerConfigFilePath(value); };
}

LeafOptionsParser::Notifier::Notifier(process_manager::LeafProcessManagerOptions *const leafServerOptions)
    : _leafProcessManagerOptions(leafServerOptions)
{
}

}// namespace leaf
