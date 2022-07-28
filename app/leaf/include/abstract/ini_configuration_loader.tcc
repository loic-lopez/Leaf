//
// Created by LoicL on 05/12/2020.
//

#ifndef __LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP__
#define __LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP__

#include "abstract/ini_configuration_loader.hpp"
#include "defines/logger_defines.hpp"
#include "exception/ini_property_in_section_exception.hpp"
#include "exception/ini_section_not_found.hpp"
#include "exception/leaf_server_config_dir_not_found.hpp"
#include "log/logger_wrapper.hpp"

#include <boost/format.hpp>

#include <source_location>
#include <utility>

namespace leaf::abstract
{

template<template<class> class StlMemoryContainer, class Model>
INIConfigurationLoader<StlMemoryContainer, Model>::INIConfigurationLoader(std::vector<IniSection> sections) : _sections(std::move(sections))
{
}

template<template<class> class StlMemoryContainer, class Model>
template<leaf::concepts::LeafExceptionClass LeafException>
boost::property_tree::ptree INIConfigurationLoader<StlMemoryContainer, Model>::initializeBoostPtree(const defines::Path &configFilePath)
{
  if (!std::filesystem::exists(configFilePath) || std::filesystem::is_directory(configFilePath))
  {
    BOOST_THROW_EXCEPTION(LeafException(configFilePath, errno, std::source_location::current()));
  }

  boost::property_tree::ptree pTree;
  boost::property_tree::ini_parser::read_ini(configFilePath.string(), pTree);

  checkForPtreeIntegrity(pTree, configFilePath);

  return pTree;
}

template<template<class> class StlMemoryContainer, class Model>
void INIConfigurationLoader<StlMemoryContainer, Model>::checkForPtreeIntegrity(
  const boost::property_tree::ptree &pTree, const defines::Path &configFilePath
) const
{
  for (const auto &section : _sections)
  {
    const defines::ini::Property sectionName = section.name;

    if (pTree.find(sectionName.data()) == pTree.not_found())
    {
      BOOST_THROW_EXCEPTION(exception::IniSectionNotFound(sectionName, configFilePath, std::source_location::current()));
    }

    for (const defines::ini::Property &property : section.properties)
    {
      if (const auto propertyCount = pTree.find(sectionName.data())->second.count(property.data()); propertyCount == 0)
        BOOST_THROW_EXCEPTION(exception::IniPropertyInSectionException(
          exception::IniPropertyInSectionException::ExceptionType::MISSING, property, sectionName, configFilePath,
          std::source_location::current()
        ));
    }
  }
}

template<template<class> class StlMemoryContainer, class Model>
template<class Callable>
void INIConfigurationLoader<StlMemoryContainer, Model>::checkValue(
  const defines::ini::Section &sectionName, const defines::ini::Property &property, const defines::Path &configFilePath,
  const Callable &toCheck
)
{
  if (toCheck())
  {
    BOOST_THROW_EXCEPTION(exception::IniPropertyInSectionException(
      exception::IniPropertyInSectionException::ExceptionType::VALUE_MISSING_OR_INVALID, property, sectionName, configFilePath,
      std::source_location::current()
    ));
  }
}

template<template<class> class StlMemoryContainer, class Model>
void INIConfigurationLoader<StlMemoryContainer, Model>::checkValue(
  const defines::ini::Section &sectionName, const defines::ini::Property &property, const defines::Path &configFilePath,
  defines::ini::PropertyValueInt &actualValue, const defines::ini::PropertyValueInt defaultValue,
  const defines::log::LoggerWrapperPtr &logger
)
{
  if (actualValue == std::numeric_limits<std::size_t>::max() || actualValue == 0)
  {
    boost::format warningFormat(
      "the ini config file located at %1% in section [%2%] value of property %3% is invalid and will be defaulted to %4%."
    );
    warningFormat % configFilePath % sectionName % property % defaultValue;
    logger->warn(warningFormat.str());
    actualValue = defaultValue;
  }
}

}// namespace leaf::abstract

#endif// __LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP__
