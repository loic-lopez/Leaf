//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_MAIN_SERVER_OPTIONS_HPP
#define LEAF_MAIN_SERVER_OPTIONS_HPP

#include <string>

#include <boost/filesystem/path.hpp>

namespace leaf::process_manager
{

class LeafProcessManagerOptions
{
  private:
    std::string _serverConfigFilePath;

  public:
    [[nodiscard]] const std::string &getServerConfigFilePath() const;

    void setServerConfigFilePath(const std::string &serverConfigFilePath);
};
}// namespace leaf::process_manager

#endif// LEAF_MAIN_SERVER_OPTIONS_HPP
