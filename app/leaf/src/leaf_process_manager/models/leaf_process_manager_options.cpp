//
// Created by LoicL on 12/12/2020.
//

#include "leaf_process_manager/models/leaf_process_manager_options.hpp"

const std::string &Leaf::LeafProcessManager::Models::LeafProcessManagerOptions::getServerConfigFilePath() const {
    return _serverConfigFilePath;
}

void Leaf::LeafProcessManager::Models::LeafProcessManagerOptions::setServerConfigFilePath(
        const std::string &serverConfigFilePath) {
    _serverConfigFilePath = serverConfigFilePath;
}
