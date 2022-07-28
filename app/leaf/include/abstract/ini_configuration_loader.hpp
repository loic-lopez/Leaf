//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_HPP
#define LEAF_INI_CONFIGURATION_LOADER_HPP

#include "concept/leaf_concepts.hpp"
#include "defines/leaf_defines.hpp"
#include "defines/logger_defines.hpp"
#include "log/logger_wrapper.hpp"

#include <boost/property_tree/ini_parser.hpp>

#include <filesystem>
#include <string>

namespace leaf::abstract
{

template<template<class> class StlMemoryContainer, class Model>
class INIConfigurationLoader
{
  public:
    virtual StlMemoryContainer<Model> load(const defines::Path &configFilePath) = 0;
    virtual ~INIConfigurationLoader()                                           = default;

  protected:
    struct IniSection
    {
        defines::ini::Property name;
        defines::ini::PropertiesContainer properties;
    };

    explicit INIConfigurationLoader(std::vector<IniSection> sections);

    const std::vector<IniSection> _sections;

    template<leaf::concepts::LeafExceptionClass LeafException>
    boost::property_tree::ptree initializeBoostPtree(const defines::Path &configFilePath);

    void checkForPtreeIntegrity(const boost::property_tree::ptree &pTree, const defines::Path &configFilePath) const;

    template<class Callable>
    static void checkValue(
      const defines::ini::Section &sectionName, const defines::ini::Property &property, const defines::Path &configFilePath,
      const Callable &toCheck
    );
    static void checkValue(
      const defines::ini::Section &sectionName, const defines::ini::Property &property, const defines::Path &configFilePath,
      defines::ini::PropertyValueInt &actualValue, defines::ini::PropertyValueInt defaultValue, const defines::log::LoggerWrapperPtr &logger
    );
};

}// namespace leaf::abstract

#include "abstract/ini_configuration_loader.tcc"

#endif// LEAF_INI_CONFIGURATION_LOADER_HPP
