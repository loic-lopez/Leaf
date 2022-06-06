//
// Created by LoicL on 05/12/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
#define LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP

#include <source_location>
#include <utility>

#include <boost/current_function.hpp>

#include "exception/ini_property_in_section_exception.hpp"
#include "exception/ini_section_not_found.hpp"

namespace leaf::abstract
{
template<template<class> class stl_memory_container, class Model>
template<leaf::concepts::LeafExceptionClass LeafException>
boost::property_tree::ptree INIConfigurationLoader<stl_memory_container, Model>::initializeBoostPtree(const std::string &configFilePath)
{
  if (!boost::filesystem::exists(configFilePath) || boost::filesystem::is_directory(configFilePath))
  {
    BOOST_THROW_EXCEPTION(LeafException(configFilePath, errno, std::source_location::current()));
  }

  boost::property_tree::ptree pTree;

  boost::property_tree::ini_parser::read_ini(configFilePath, pTree);

  checkForPtreeIntegrity(pTree, configFilePath);

  return pTree;
}

template<template<class> class stl_memory_container, class Model>
void INIConfigurationLoader<stl_memory_container, Model>::checkForPtreeIntegrity(
  const boost::property_tree::ptree &pTree, const std::string &configFilePath
)
{
  for (const auto &section : _sections)
  {
    const PropertyString sectionName = section.name;

    if (pTree.find(sectionName.data()) == pTree.not_found())
    {
      BOOST_THROW_EXCEPTION(exception::IniSectionNotFound(sectionName, configFilePath, std::source_location::current()));
    }

    for (const PropertyString &property : section.properties)
    {
      const auto propertyCount = pTree.find(sectionName.data())->second.count(property.data());
      if (propertyCount == 0)
        BOOST_THROW_EXCEPTION(exception::IniPropertyInSectionException(
          exception::IniPropertyInSectionException::ExceptionType::MISSING, property, sectionName, configFilePath,
          std::source_location::current()
        ));
    }
  }
}

template<template<class> class stl_memory_container, class Model>
INIConfigurationLoader<stl_memory_container, Model>::INIConfigurationLoader(std::vector<IniSection> sections)
    : _sections(std::move(sections))
{
}

}// namespace leaf::abstract

#endif// LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
