//
// Created by LoicL on 23/12/2020.
//

#include <iostream>
#include "utils/utils.hpp"

std::string Leaf::Utils::BuildInfo() {
    return Leaf::Build::LeafVersion
           + ", build type: " + Leaf::Build::LeafBuildType + " [" + Leaf::Build::Arch + "]"
           + ", build date: " + Leaf::Build::LeafBuildDate;
}
