//
// Created by LoicL on 12/12/2020.
//

#include <iostream>
#include <boost/program_options/parsers.hpp>
#include "server/leaf_build.hpp"
#include "server/leaf_server_options_parser.hpp"

Leaf::LeafServer::ServerOptionsParser::ServerOptionsParser(Models::ServerOptions *serverOptions) :
        _serverCliOptionsDescription(std::string("Leaf: ") + LeafVersion + " available options"),
        _serverOptions(serverOptions) {

    _serverCliOptionsDescription.add_options()
            (CliOptions::HELP, "produce help message")
            (CliOptions::SERVER_CONFIG_FILE, boost::program_options::value<std::string>(),
             "set the config .ini file path for the server.");

    _serverEnvOptionsDescription.add_options()
            (EnvOptions::SERVER_CONFIG_FILE, boost::program_options::value<std::string>(),
             "set the config .ini file path for the server.");
}

void Leaf::LeafServer::ServerOptionsParser::parseCommandLineArgs(int ac, const char **av) {
    boost::program_options::variables_map commandLineArgs;

    boost::program_options::store(
            boost::program_options::parse_command_line(ac, av, _serverCliOptionsDescription),
            commandLineArgs
    );
    boost::program_options::notify(commandLineArgs);


    if (commandLineArgs.count(CliOptions::SERVER_CONFIG_FILE) == 0 || commandLineArgs.count(CliOptions::HELP)) {
        std::cout << _serverCliOptionsDescription << std::endl;
    }
}

/*const std::string &Leaf::LeafServer::ServerOptionsParser::getServerConfigFilePath() {
    return nullptr; //_commandLineArgs[Options::SERVER_CONFIG_FILE].as<std::string>();
}*/


void Leaf::LeafServer::ServerOptionsParser::parseEnvironment() {
    boost::program_options::variables_map envVars;

    boost::program_options::store(
            boost::program_options::parse_environment(_serverEnvOptionsDescription, [this](const std::string &envVar) {
                bool matched = std::any_of(
                        this->_serverEnvOptionsDescription.options().cbegin(),
                        this->_serverEnvOptionsDescription.options().cend(),
                        [envVar](auto opt) { return envVar == opt->long_name(); });
                return matched ? envVar : "";
            }),
            envVars
    );
    boost::program_options::notify(envVars);

/*    for (auto envVar : envVars) {
        std::cout << "env.first: " << envVar.first << " env.second " << envVar.second.as<std::string>() << std::endl;
    }*/
}