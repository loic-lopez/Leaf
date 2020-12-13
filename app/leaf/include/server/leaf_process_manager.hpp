//
// Created by LoicL on 13/12/2020.
//

#ifndef LEAF_PROCESS_MANAGER_HPP
#define LEAF_PROCESS_MANAGER_HPP

#include "server/leaf_server.hpp"
#include "server/models/leaf_server_configuration.hpp"
#include "leaf_server_options_parser.hpp"

namespace Leaf::LeafServer {
    class LeafProcessManager {
    private:
        int _ac;
        const char **_av;
        Models::LeafServerOptions *_leafServerOptions;
        Models::LeafServerConfiguration *_leafServerConfiguration;
        std::vector<LeafServer> _leafServers;

    private:
        void onStart();

        void startServers();

        void loadLeafConfiguration();

        void waitForServers();

        void parseCommandLineArgs();

    public:
        void start();

        LeafProcessManager(int ac, const char **av);

        virtual ~LeafProcessManager();
    };
}


#endif //LEAF_PROCESS_MANAGER_HPP
