//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP
#define LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP

#include <string>

namespace leaf::process_manager
{

class LeafProcessManagerConfiguration
{
  public:
    explicit LeafProcessManagerConfiguration(
      const std::string &serversRootPath, const std::string &leafLogDirectoryPath, std::size_t leafLogMaxFileSize,
      std::size_t leafLogMaxFiles, const std::string &mimeTypesConfigFilePath
    );

    [[nodiscard]] const std::string &getServersRootPath() const;

    [[nodiscard]] const std::string &getLeafLogDirectoryPath() const;
    [[nodiscard]] std::size_t getLeafLogMaxFileSize() const;
    [[nodiscard]] std::size_t getLeafLogMaxFiles() const;

    [[nodiscard]] const std::string &getMimeTypesConfigFilePath() const;

  private:
    const std::string _serversRootPath;
    const std::string _leafLogDirectoryPath;
    const std::size_t _leafLogMaxFileSize;
    const std::size_t _leafLogMaxFiles;
    const std::string _mimeTypesConfigFilePath;
};

}// namespace leaf::process_manager

#endif// LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP
