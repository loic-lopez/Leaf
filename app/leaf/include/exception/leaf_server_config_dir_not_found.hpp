//
// Created by loicl on 5/9/2022.
//

#ifndef __LEAF_SERVER_CONF_DIR_NOT_FOUND_HPP__
#define __LEAF_SERVER_CONF_DIR_NOT_FOUND_HPP__

#include "exception/abstract/exception.hpp"

namespace leaf::exception
{
class LeafServerConfigDirNotFound : public abstract::Exception
{
 private:
  std::string _configurationDirectory;
 public:
  explicit LeafServerConfigDirNotFound(const std::string_view &configurationDirectory, const std::source_location &location);
  virtual ~LeafServerConfigDirNotFound() = default;

 protected:
  void buildStdExceptionMessage(const char *exceptionClassName) override;
};
}

#endif// __LEAF_SERVER_CONF_DIR_NOT_FOUND_HPP__
