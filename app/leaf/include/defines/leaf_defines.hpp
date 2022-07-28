//
// Created by loicl on 7/28/2022.
//

#ifndef __LEAF_LEAF_DEFINES_HPP__
#define __LEAF_LEAF_DEFINES_HPP__

#include <filesystem>
#include <vector>
#include <source_location>

namespace leaf::defines
{
using Path = std::filesystem::path;

namespace ini
{
using Property            = std::string_view;
using Section             = std::string_view;
using PropertiesContainer = std::vector<Property>;

using PropertyValueString = std::string;
using PropertyValueInt    = std::size_t;

}// namespace ini

}// namespace leaf::defines

#endif// __LEAF_LEAF_DEFINES_HPP__
