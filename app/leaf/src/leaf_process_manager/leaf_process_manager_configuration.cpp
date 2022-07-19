//
// Created by LoicL on 19/12/2020.
//

#include "leaf_process_manager/leaf_process_manager_configuration.hpp"

#include <boost/filesystem/operations.hpp>

#include <utility>

namespace leaf::process_manager
{

LeafProcessManagerConfiguration::LeafProcessManagerConfiguration(
  const std::string &serversRootPath, const std::string &leafLogDirectoryPath, const std::size_t leafLogMaxFileSize,
  const std::size_t leafLogMaxFiles, const std::string &mimeTypesConfigFilePath
)
    : _serversRootPath(boost::filesystem::weakly_canonical(serversRootPath).string()),
      _leafLogDirectoryPath(boost::filesystem::weakly_canonical(leafLogDirectoryPath).string()),
      _leafLogMaxFileSize(leafLogMaxFileSize),
      _leafLogMaxFiles(leafLogMaxFiles),
      _mimeTypesConfigFilePath(boost::filesystem::weakly_canonical(mimeTypesConfigFilePath).string())
{
}

const std::string &LeafProcessManagerConfiguration::getServersRootPath() const { return _serversRootPath; }

const std::string &LeafProcessManagerConfiguration::getLeafLogDirectoryPath() const { return _leafLogDirectoryPath; }

const std::string &LeafProcessManagerConfiguration::getMimeTypesConfigFilePath() const { return _mimeTypesConfigFilePath; }

std::size_t LeafProcessManagerConfiguration::getLeafLogMaxFileSize() const { return _leafLogMaxFileSize; }

std::size_t LeafProcessManagerConfiguration::getLeafLogMaxFiles() const { return _leafLogMaxFiles; }

}// namespace leaf::process_manager
