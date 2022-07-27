//
// Created by LoicL on 19/12/2020.
//

#ifndef __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP__
#define __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP__

#include <string>

namespace leaf::process_manager
{

class LeafProcessManagerConfiguration
{
  public:
    explicit LeafProcessManagerConfiguration(
      const std::string &serversRootPath, const std::string &leafLogDirectoryPath, std::size_t leafLogMaxFileSize,
      std::size_t leafLogMaxFiles, const std::size_t leafLogThreadsPerLeafServer, std::string mimeTypesConfigFilePath
    );

    [[nodiscard]] const std::string &getServersRootPath() const;

    [[nodiscard]] const std::string &getLeafLogDirectoryPath() const;
    [[nodiscard]] std::size_t getLeafLogMaxFileSize() const;
    [[nodiscard]] std::size_t getLeafLogMaxFiles() const;
    [[nodiscard]] std::size_t getLeafLogThreadsPerLeafServer() const;

    [[nodiscard]] const std::string &getMimeTypesConfigFilePath() const;

  private:
    const std::string _serversRootPath;
    const std::string _leafLogDirectoryPath;
    const std::size_t _leafLogMaxFileSize;
    const std::size_t _leafLogMaxFiles;
    const std::size_t _leafLogThreadsPerLeafServer;
    const std::string _mimeTypesConfigFilePath;
};

}// namespace leaf::process_manager

#endif// __LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP__
