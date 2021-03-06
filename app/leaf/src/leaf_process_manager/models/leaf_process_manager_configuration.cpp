//
// Created by LoicL on 19/12/2020.
//

#include <utility>
#include "leaf_process_manager/models/leaf_process_manager_configuration.hpp"

Leaf::LeafProcessManager::Models::LeafProcessManagerConfiguration::LeafProcessManagerConfiguration(
        std::string serversRootPath,
        std::string leafLogDirectory,
        std::string mimeTypesConfigFile
) :
        serversRootPath(std::move(serversRootPath)),
        leafLogDirectory(std::move(leafLogDirectory)),
        mimeTypesConfigFile(std::move(mimeTypesConfigFile)) {

}
