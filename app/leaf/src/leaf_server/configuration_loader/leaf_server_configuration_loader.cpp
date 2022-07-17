//
// Created by LoicL on 06/03/2021.
//

#include "exception/leaf_server_config_file_not_found.hpp"
#include "leaf_server/configuration_loader/leaf_server_configuration_loader.hpp"

namespace leaf::server
{
std::shared_ptr<LeafServerConfiguration> configuration_loader::LeafServerConfigurationLoader::load(const std::string &configFilePath)
{
  boost::property_tree::ptree pTree = this->initializeBoostPtree<exception::LeafServerConfigFileNotFound>(configFilePath);

  int port              = pTree.get_child(LEAF_SERVER_SECTION.data()).get_child("port").get_value<int>();
  auto documentRootPath = pTree.get_child(LEAF_SERVER_SECTION.data()).get_child("document_root_path").get_value<std::string>();
  auto listenAddr       = pTree.get_child(LEAF_SERVER_SECTION.data()).get_child("listen_addr").get_value<std::string>();

  return std::make_shared<LeafServerConfiguration>(port, documentRootPath, listenAddr);
}

configuration_loader::LeafServerConfigurationLoader::LeafServerConfigurationLoader()
    : INIConfigurationLoader<std::shared_ptr, LeafServerConfiguration>({{.name = LEAF_SERVER_SECTION, .properties = _properties}})
{
}

}// namespace leaf::server
