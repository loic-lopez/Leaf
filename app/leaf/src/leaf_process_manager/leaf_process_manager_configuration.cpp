//
// Created by LoicL on 19/12/2020.
//

#include <utility>

#include <boost/filesystem/operations.hpp>

#include "leaf_process_manager/leaf_process_manager_configuration.hpp"

namespace leaf::process_manager
{

LeafProcessManagerConfiguration::LeafProcessManagerConfiguration(const std::string &serversRootPath,
                                                                 const std::string &leafLogDirectoryPath,
                                                                 const std::string &mimeTypesConfigFilePath)
    : serversRootPath(boost::filesystem::weakly_canonical(serversRootPath).string()),
      leafLogDirectoryPath(boost::filesystem::weakly_canonical(leafLogDirectoryPath).string()),
      mimeTypesConfigFilePath(boost::filesystem::weakly_canonical(mimeTypesConfigFilePath).string())
{
}

const std::string &LeafProcessManagerConfiguration::getServersRootPath() const { return serversRootPath; }

const std::string &LeafProcessManagerConfiguration::getLeafLogDirectoryPath() const { return leafLogDirectoryPath; }

const std::string &LeafProcessManagerConfiguration::getMimeTypesConfigFilePath() const { return mimeTypesConfigFilePath; }

}// namespace leaf::process_manager
