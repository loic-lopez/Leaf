//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
#define LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP

#include "abstract/ini_configuration_loader.hpp"
#include "leaf_server/leaf_server_configuration.hpp"

namespace leaf::server::configuration_loader
{

using std::string_view_literals::operator""sv;

class LeafServerConfigurationLoader : public abstract::INIConfigurationLoader<std::shared_ptr, LeafServerConfiguration>
{
  public:
    inline static constinit PropertyString LEAF_SERVER_SECTION = "LeafServer"sv;

    std::shared_ptr<LeafServerConfiguration> load(const std::string &configFilePath) override;

    explicit LeafServerConfigurationLoader();
    virtual ~LeafServerConfigurationLoader() = default;

  private:
    inline static const PropertiesContainer _properties = {{"port"sv}, {"document_root_path"sv}, {"listen_addr"sv}};
};

}// namespace leaf::server::configuration_loader

#endif// LEAF_LEAF_SERVER_CONFIGURATION_LOADER_HPP
