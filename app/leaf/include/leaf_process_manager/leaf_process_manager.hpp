//
// Created by LoicL on 13/12/2020.
//

#ifndef LEAF_PROCESS_MANAGER_HPP
#define LEAF_PROCESS_MANAGER_HPP

#include "leaf_server/leaf_server.hpp"
#include "leaf_process_manager/models/leaf_process_manager_configuration.hpp"
#include "leaf_options_parser/leaf_options_parser.hpp"

namespace Leaf::LeafProcessManager {
    class LeafProcessManager {
    private:
        std::unique_ptr<Models::LeafProcessManagerOptions> _processManagerOptions;
        std::unique_ptr<Models::LeafProcessManagerConfiguration> _processManagerConfiguration;
        std::vector<LeafServer::LeafServer> _leafServers;

    private:
        void onStart();

        void startServers();

        void loadLeafConfiguration();

        void waitForServers();

    public:
        void parseCommandLineArgs(int ac, const char **av);

        void start();

        LeafProcessManager();

        virtual ~LeafProcessManager();
    };
}


#endif //LEAF_PROCESS_MANAGER_HPP
