//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_OPTIONS_PARSER_HPP
#define LEAF_OPTIONS_PARSER_HPP

#include "leaf_process_manager/leaf_process_manager_options.hpp"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#include <string>

namespace leaf
{

namespace cli_options
{
using namespace std::string_view_literals;

inline static constinit const std::string_view SERVER_CONFIG_FILE = "server-config-file"sv;
inline static constinit const std::string_view HELP               = "help"sv;
}// namespace cli_options

namespace env_options
{
using namespace std::string_view_literals;

inline static constinit const std::string_view SERVER_CONFIG_FILE = "LEAF_SERVER_CONFIG_FILE"sv;
inline static constinit const std::string_view ENV_PREFIX         = "LEAF_"sv;
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

    explicit LeafOptionsParser(process_manager::LeafProcessManagerOptions *serverOptions);
    Status parseCommandLineArgs(int ac, const char **av);
    void parseEnvironment() const;
    void displayHelp() const;

  protected:
    [[nodiscard]] std::string matchEnvironmentVariable(const std::string &envVar) const;

  private:
    struct CallbackReceiver
    {
        std::function<CallbackThatTriggersHelp> optionVerifier;
        Status statusWhenOptionVerifierMatched;
    };

    class Notifier
    {
      public:
        explicit Notifier(process_manager::LeafProcessManagerOptions *leafServerOptions);
        std::function<void(const std::string &)> makeServerConfigFileNotifier();

      private:
        process_manager::LeafProcessManagerOptions *const _leafProcessManagerOptions;
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
};

}// namespace leaf

#endif// LEAF_OPTIONS_PARSER_HPP
