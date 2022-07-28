//
// Created by LoicL on 19/12/2020.
//

#include "leaf_process_manager/leaf_process_manager_configuration.hpp"

#include <boost/filesystem/operations.hpp>

#include <utility>

namespace leaf::process_manager
{

LeafProcessManagerConfiguration::LeafProcessManagerConfiguration(
  defines::Path serversRootPath, defines::Path leafLogDirectoryPath, const std::size_t leafLogMaxFileSize,
  const std::size_t leafLogMaxFiles, const std::size_t leafLogThreadsPerLeafServer, defines::Path mimeTypesConfigFilePath
)
    : _serversRootPath(std::move(serversRootPath)),
      _leafLogDirectoryPath(std::move(leafLogDirectoryPath)),
      _leafLogMaxFileSize(leafLogMaxFileSize),
      _leafLogMaxFiles(leafLogMaxFiles),
      _leafLogThreadsPerLeafServer(leafLogThreadsPerLeafServer),
      _mimeTypesConfigFilePath(std::move(mimeTypesConfigFilePath))
{
}

const defines::Path &LeafProcessManagerConfiguration::getServersRootPath() const { return _serversRootPath; }

const defines::Path &LeafProcessManagerConfiguration::getLeafLogDirectoryPath() const { return _leafLogDirectoryPath; }

const defines::Path &LeafProcessManagerConfiguration::getMimeTypesConfigFilePath() const { return _mimeTypesConfigFilePath; }

std::size_t LeafProcessManagerConfiguration::getLeafLogMaxFileSize() const { return _leafLogMaxFileSize; }

std::size_t LeafProcessManagerConfiguration::getLeafLogMaxFiles() const { return _leafLogMaxFiles; }

std::size_t LeafProcessManagerConfiguration::getLeafLogThreadsPerLeafServer() const { return _leafLogThreadsPerLeafServer; }

}// namespace leaf::process_manager
