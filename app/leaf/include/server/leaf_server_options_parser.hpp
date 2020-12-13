//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_SERVER_OPTIONS_PARSER_HPP
#define LEAF_SERVER_OPTIONS_PARSER_HPP

#include <string>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include "server/models/leaf_server_options.hpp"

namespace Leaf::LeafServer {
    namespace CliOptions {
        inline static const char SERVER_CONFIG_FILE[] = "server-config-file";
        inline static const char HELP[] = "help";
    }

    namespace EnvOptions {
        inline static const char SERVER_CONFIG_FILE[] = "LEAF_SERVER_CONFIG_FILE";
        inline static const char ENV_PREFIX[] = "LEAF_";
    }

    class ServerOptionsParser {
    private:
        boost::program_options::options_description _serverCliOptionsDescription;
        boost::program_options::options_description _serverEnvOptionsDescription;
        Models::ServerOptions *_serverOptions;

    public:
        explicit ServerOptionsParser(Models::ServerOptions *serverOptions);

/*        const std::string &getServerConfigFilePath();*/

        void parseCommandLineArgs(int ac, const char **av);

        void parseEnvironment();
    };
}

#endif //LEAF_SERVER_OPTIONS_PARSER_HPP
