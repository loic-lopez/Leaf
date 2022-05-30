//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_OPTIONS_PARSER_HPP
#define LEAF_OPTIONS_PARSER_HPP

#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#include "leaf_process_manager/leaf_process_manager_options.hpp"

namespace leaf
{

namespace cli_options
{
constexpr static const char SERVER_CONFIG_FILE[] = "server-config-file";
constexpr static const char HELP[]               = "help";
}// namespace cli_options

namespace env_options
{
constexpr static const char SERVER_CONFIG_FILE[] = "LEAF_SERVER_CONFIG_FILE";
constexpr static const char ENV_PREFIX[]         = "LEAF_";
}// namespace env_options

using CallbackThatTriggersHelp = bool(const std::string &option, const boost::program_options::variables_map &commandLineArgs);

class LeafOptionsParser
{
  public:
    enum class Status : unsigned int
    {
      SUCCESS,
      NEED_DISPLAY_HELP,
      REQUIRED_OPTIONS_NOT_PRESENT
    };

  private:
    class CallbackReceiver
    {
      public:
        std::function<CallbackThatTriggersHelp> optionVerifier;
        Status statusWhenOptionVerifierMatched;
    };

    class Notifier
    {
      private:
        process_manager::LeafProcessManagerOptions *const _leafProcessManagerOptions;

      public:
        explicit Notifier(process_manager::LeafProcessManagerOptions *leafServerOptions);

        std::function<void(const std::string &)> makeServerConfigFileNotifier();
    };

    Notifier _notifier;

    boost::program_options::options_description _cliRequiredOptionsDescription =
      boost::program_options::options_description("Required arguments");
    boost::program_options::options_description _cliOptionalOptionsDescription =
      boost::program_options::options_description("Optional arguments");
    boost::program_options::options_description _envOptionsDescription;
    process_manager::LeafProcessManagerOptions *const _leafProcessManagerOptions;

    std::map<std::string, CallbackReceiver> _callbacksThatTriggersHelp;
    boost::program_options::typed_value<std::string> *_configFileValue;

  protected:
    [[nodiscard]] std::string matchEnvironmentVariable(const std::string &envVar) const;

  public:
    explicit LeafOptionsParser(process_manager::LeafProcessManagerOptions *serverOptions);

    Status parseCommandLineArgs(int ac, const char **av);

    void parseEnvironment() const;

    void displayHelp() const;
};
}// namespace leaf

#endif// LEAF_OPTIONS_PARSER_HPP
