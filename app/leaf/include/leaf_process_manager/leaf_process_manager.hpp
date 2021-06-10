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
        void displayBanner() const;

        void startServers() const;

        void loadLeafConfiguration();

        void waitForServers() const;

        LeafProcessManager() = default;

    public:
        void parseCommandLineArgs(int ac, const char **av) const;

        void start();

        virtual ~LeafProcessManager();

        static LeafProcessManager &GetInstance();

        LeafProcessManager(const LeafProcessManager &) = delete;

        LeafProcessManager &operator=(const LeafProcessManager) = delete;

        LeafProcessManager(LeafProcessManager &&) = delete;

        LeafProcessManager &operator=(LeafProcessManager &&) = delete;

    private:
        std::unique_ptr<Models::LeafProcessManagerOptions> _processManagerOptions =
                std::make_unique<Models::LeafProcessManagerOptions>();
        std::unique_ptr<Models::LeafProcessManagerConfiguration> _processManagerConfiguration;
        std::vector<std::shared_ptr<LeafServer::LeafServer>> _leafServers;
    };
}


#endif //LEAF_PROCESS_MANAGER_HPP
