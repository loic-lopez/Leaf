//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_MAIN_SERVER_OPTIONS_HPP
#define LEAF_MAIN_SERVER_OPTIONS_HPP

#include <boost/filesystem/path.hpp>

#include <string>

namespace leaf::process_manager
{

class LeafProcessManagerOptions
{
  public:
    [[nodiscard]] const std::string &getServerConfigFilePath() const;
    void setServerConfigFilePath(const std::string &serverConfigFilePath);

  private:
    std::string _serverConfigFilePath;
};

}// namespace leaf::process_manager

#endif// LEAF_MAIN_SERVER_OPTIONS_HPP
