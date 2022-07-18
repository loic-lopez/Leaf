//
// Created by LoicL on 23/12/2020.
//

#include "utils/leaf_build.hpp"
#include "utils/utils.hpp"

#include <boost/format.hpp>

#include <string_view>

namespace leaf::utils
{

std::string BuildInfo()
{
  const boost::format buildInfo = boost::format("%1%: %2%, build type: %3% [%4%], build date: %5%") % build::LeafProjectName
    % build::LeafVersion % build::LeafBuildType % build::Arch % build::LeafBuildDate;
  return buildInfo.str();
}

}// namespace leaf::utils
