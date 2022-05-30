//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP

#include "abstract/ini_configuration_loader.hpp"
#include "leaf_server/leaf_server_configuration.hpp"

namespace leaf::server::configuration_loader
{
class LeafServerConfigurationLoader : public abstract::INIConfigurationLoader<std::shared_ptr, LeafServerConfiguration>
{
  private:
    inline static const std::vector<std::string> _properties = {{"port"}, {"document_root_path"}, {"listen_addr"}};

  public:
    constexpr static const char LEAF_SERVER_SECTION[] = "LeafServer";

    std::shared_ptr<LeafServerConfiguration> load(const std::string &configFilePath) override;

    explicit LeafServerConfigurationLoader();
    virtual ~LeafServerConfigurationLoader() = default;
};
}// namespace leaf::server::configuration_loader

#endif// LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
