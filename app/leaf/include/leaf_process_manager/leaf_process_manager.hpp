//
// Created by LoicL on 13/12/2020.
//

#ifndef LEAF_PROCESS_MANAGER_HPP
#define LEAF_PROCESS_MANAGER_HPP

#include "leaf_options_parser/leaf_options_parser.hpp"
#include "leaf_process_manager_configuration.hpp"
#include "leaf_server/leaf_server.hpp"

namespace leaf::process_manager
{

class LeafProcessManager
{
  public:
    virtual ~LeafProcessManager() = default;

    void parseCommandLineArgs(int ac, const char **av) const;
    void start();

    static LeafProcessManager &GetInstance();

    LeafProcessManager(const LeafProcessManager &)          = delete;
    LeafProcessManager &operator=(const LeafProcessManager) = delete;
    LeafProcessManager(LeafProcessManager &&)               = delete;
    LeafProcessManager &operator=(LeafProcessManager &&)    = delete;

  private:
    std::unique_ptr<LeafProcessManagerOptions> _processManagerOptions = std::make_unique<LeafProcessManagerOptions>();
    std::unique_ptr<LeafProcessManagerConfiguration> _processManagerConfiguration;
    std::vector<std::shared_ptr<server::LeafServer>> _leafServers;

    LeafProcessManager() = default;
    void displayBanner() const;
    void startServers() const;
    void waitForServers() const;
    void loadLeafConfiguration();
};

}// namespace leaf::process_manager

#endif// LEAF_PROCESS_MANAGER_HPP
