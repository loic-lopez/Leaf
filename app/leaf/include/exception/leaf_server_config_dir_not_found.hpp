//
// Created by loicl on 5/9/2022.
//

#ifndef __LEAF_SERVER_CONF_DIR_NOT_FOUND_HPP__
#define __LEAF_SERVER_CONF_DIR_NOT_FOUND_HPP__

#include "defines/leaf_defines.hpp"
#include "exception/abstract/exception.hpp"

namespace leaf::exception
{
class LeafServerConfigDirNotFound : public abstract::Exception
{
  public:
    explicit LeafServerConfigDirNotFound(const defines::Path &configurationDirectory, const std::source_location &location);
    virtual ~LeafServerConfigDirNotFound() = default;

  protected:
    void buildStdExceptionMessage(const char *exceptionClassName) override;

  private:
    defines::Path _configurationDirectory;
};
}// namespace leaf::exception

#endif// __LEAF_SERVER_CONF_DIR_NOT_FOUND_HPP__
