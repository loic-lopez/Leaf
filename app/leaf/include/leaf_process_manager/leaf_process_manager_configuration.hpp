//
// Created by LoicL on 19/12/2020.
//

#ifndef __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP__
#define __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP__

#include "defines/leaf_defines.hpp"

#include <string>

namespace leaf::process_manager
{

class LeafProcessManagerConfiguration
{
  public:
    explicit LeafProcessManagerConfiguration(
      defines::Path serversRootPath, defines::Path leafLogDirectoryPath, std::size_t leafLogMaxFileSize, std::size_t leafLogMaxFiles,
      std::size_t leafLogThreadsPerLeafServer, defines::Path mimeTypesConfigFilePath
    );

    [[nodiscard]] const defines::Path &getServersRootPath() const;

    [[nodiscard]] const defines::Path &getLeafLogDirectoryPath() const;
    [[nodiscard]] std::size_t getLeafLogMaxFileSize() const;
    [[nodiscard]] std::size_t getLeafLogMaxFiles() const;
    [[nodiscard]] std::size_t getLeafLogThreadsPerLeafServer() const;

    [[nodiscard]] const defines::Path &getMimeTypesConfigFilePath() const;

  private:
    const defines::Path _serversRootPath;
    const defines::Path _leafLogDirectoryPath;
    const std::size_t _leafLogMaxFileSize;
    const std::size_t _leafLogMaxFiles;
    const std::size_t _leafLogThreadsPerLeafServer;
    const defines::Path _mimeTypesConfigFilePath;
};

}// namespace leaf::process_manager

#endif// __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP__
