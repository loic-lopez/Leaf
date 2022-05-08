//
// Created by LoicL on 12/12/2020.
//

#include "leaf_process_manager/leaf_process_manager_options.hpp"

#include <boost/filesystem/operations.hpp>

namespace leaf::process_manager
{
const std::string &LeafProcessManagerOptions::getServerConfigFilePath() const { return _serverConfigFilePath; }

void LeafProcessManagerOptions::setServerConfigFilePath(const std::string &serverConfigFilePath)
{
  _serverConfigFilePath = boost::filesystem::weakly_canonical(serverConfigFilePath).string();
}
}// namespace leaf::process_manager
