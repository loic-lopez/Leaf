//
// Created by LoicL on 23/12/2020.
//

#include <string>

#include <boost/format.hpp>

#include "utils/leaf_build.hpp"
#include "utils/utils.hpp"

namespace leaf::utils
{

std::string BuildInfo()
{
  return build::LeafVersion + ", build type: " + build::LeafBuildType + " [" + build::Arch + "]" + ", build date: " + build::LeafBuildDate;
}

}// namespace leaf::utils
