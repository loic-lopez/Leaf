//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_OPTIONS_PARSER_HPP
#define LEAF_OPTIONS_PARSER_HPP

#include <string>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include "leaf_process_manager/models/leaf_process_manager_options.hpp"

namespace Leaf {

    using namespace LeafProcessManager;

    namespace CliOptions {
        inline static const char SERVER_CONFIG_FILE[] = "server-config-file";
        inline static const char HELP[] = "help";
    }

    namespace EnvOptions {
        inline static const char SERVER_CONFIG_FILE[] = "LEAF_SERVER_CONFIG_FILE";
        inline static const char ENV_PREFIX[] = "LEAF_";
    }

    using CallbackThatTriggersHelp =
    bool(const std::string &option, const boost::program_options::variables_map &commandLineArgs);

    class LeafOptionsParser {
    public:
        enum class Status : unsigned int {
            SUCCESS,
            NEED_DISPLAY_HELP,
            REQUIRED_OPTIONS_NOT_PRESENT
        };

    private:
        class CallbackReceiver {
        public:
            std::function<CallbackThatTriggersHelp> optionVerifier;
            Status statusWhenOptionVerifierMatched;
        };

        class Notifier {
        private:
            Models::LeafProcessManagerOptions *const _leafServerOptions;

        public:
            explicit Notifier(Models::LeafProcessManagerOptions *leafServerOptions);

            std::function<void(const std::string &)> makeServerConfigFileNotifier();
        };

        Notifier _notifier;

        boost::program_options::options_description _cliRequiredOptionsDescription = boost::program_options::options_description("Required arguments");
        boost::program_options::options_description _cliOptionalOptionsDescription = boost::program_options::options_description("Optional arguments");
        boost::program_options::options_description _envOptionsDescription;
        Models::LeafProcessManagerOptions *const _leafProcessManagerOptions;

        std::map<std::string, CallbackReceiver> _callbacksThatTriggersHelp;
        boost::program_options::typed_value<std::string> *_configFileValue;

    protected:
        std::string matchEnvironmentVariable(const std::string &envVar);

    public:
        explicit LeafOptionsParser(Models::LeafProcessManagerOptions *serverOptions);

        Status parseCommandLineArgs(int ac, const char **av);

        void parseEnvironment();

        void displayHelp();
    };
}

#endif //LEAF_OPTIONS_PARSER_HPP
