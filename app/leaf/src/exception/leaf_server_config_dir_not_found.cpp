//
// Created by loicl on 5/9/2022.
//

#include "exception/leaf_server_config_dir_not_found.hpp"

#include <boost/format.hpp>

namespace leaf::exception
{

LeafServerConfigDirNotFound::LeafServerConfigDirNotFound(const defines::Path& configurationDirectory, const std::source_location& location)
    : Exception(location), _configurationDirectory(configurationDirectory)
{
  LeafServerConfigDirNotFound::buildStdExceptionMessage(__FUNCTION__);
}

void LeafServerConfigDirNotFound::buildStdExceptionMessage(const char* exceptionClassName)
{
  boost::format exceptionFormat("%1% exception raised:\nthis means the root config directory %2% does not exists.");
  exceptionFormat % exceptionClassName % _configurationDirectory;
  _msg = exceptionFormat.str();
}

}// namespace leaf::exception