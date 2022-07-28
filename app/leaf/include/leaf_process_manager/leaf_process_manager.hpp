//
// Created by LoicL on 13/12/2020.
//

#ifndef __LEAF_PROCESS_MANAGER_HPP__
#define __LEAF_PROCESS_MANAGER_HPP__

#include "leaf_options_parser/leaf_options_parser.hpp"
#include "leaf_process_manager/leaf_process_manager_configuration.hpp"
#include "leaf_server/leaf_server.hpp"
#include "library/singleton.hpp"
#include "log/logger_interface.hpp"

namespace leaf::process_manager
{

class LeafProcessManager final : public log::LoggerInterface, public library::Singleton<LeafProcessManager>
{
  public:
    friend class library::Singleton<LeafProcessManager>;// allow library::Singleton to create static instance of LeafProcessManager
    virtual ~LeafProcessManager();

    // methods
    void parseCommandLineArgs(int ac, const char **av) const;
    void start();

  private:
    std::unique_ptr<LeafProcessManagerOptions> _processManagerOptions = std::make_unique<LeafProcessManagerOptions>();
    std::unique_ptr<LeafProcessManagerConfiguration> _processManagerConfiguration;
    std::vector<std::shared_ptr<server::LeafServer>> _leafServers;

    // constructors
    explicit LeafProcessManager();

    // methods
    void startServers() const;
    void waitForServers() const;
    void loadLeafConfiguration();
    void initializeLoggers();

    // static
    static void DisplayBanner();
    static void SignalHandler(int signal);
    static void RegisterSignalHandlers();
};

}// namespace leaf::process_manager

#endif// __LEAF_PROCESS_MANAGER_HPP__
