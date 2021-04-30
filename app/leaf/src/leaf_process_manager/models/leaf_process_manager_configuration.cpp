//
// Created by LoicL on 19/12/2020.
//

#include <utility>
#include <boost/filesystem/operations.hpp>
#include "leaf_process_manager/models/leaf_process_manager_configuration.hpp"

Leaf::LeafProcessManager::Models::LeafProcessManagerConfiguration::LeafProcessManagerConfiguration(
        const std::string &serversRootPath,
        const std::string &leafLogDirectoryPath,
        const std::string &mimeTypesConfigFilePath
) :
        serversRootPath(boost::filesystem::canonical(serversRootPath).string()),
        leafLogDirectoryPath(boost::filesystem::canonical(leafLogDirectoryPath).string()),
        mimeTypesConfigFilePath(boost::filesystem::canonical(mimeTypesConfigFilePath).string()) {
}

const std::string &Leaf::LeafProcessManager::Models::LeafProcessManagerConfiguration::getServersRootPath() const {
    return serversRootPath;
}

const std::string &Leaf::LeafProcessManager::Models::LeafProcessManagerConfiguration::getLeafLogDirectoryPath() const {
    return leafLogDirectoryPath;
}

const std::string &
Leaf::LeafProcessManager::Models::LeafProcessManagerConfiguration::getMimeTypesConfigFilePath() const {
    return mimeTypesConfigFilePath;
}
