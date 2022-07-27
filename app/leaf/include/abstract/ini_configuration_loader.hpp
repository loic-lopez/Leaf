//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_HPP
#define LEAF_INI_CONFIGURATION_LOADER_HPP

#include "concept/leaf_concepts.hpp"
#include "log/logger_defines.hpp"
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
    virtual StlMemoryContainer<Model> load(const std::string &configFilePath) = 0;
    virtual ~INIConfigurationLoader()                                         = default;

  protected:
    using PropertyString      = std::string_view;
    using PropertiesContainer = std::vector<PropertyString>;

    struct IniSection
    {
        PropertyString name;
        PropertiesContainer properties;
    };

    explicit INIConfigurationLoader(std::vector<IniSection> sections);

    const std::vector<IniSection> _sections;

    template<leaf::concepts::LeafExceptionClass LeafException>
    boost::property_tree::ptree initializeBoostPtree(const std::string &configFilePath);

    void checkForPtreeIntegrity(const boost::property_tree::ptree &pTree, const std::string &configFilePath);

    static void checkValue(
      const std::string_view &sectionName, const std::string &property, const std::string &configFilePath,
      const std::function<bool()> &toCheck
    );
    static void checkValue(
      const std::string_view &sectionName, const std::string &property, const std::string &configFilePath, std::size_t &actualValue,
      const size_t defaultValue, const log::LoggerWrapperPtr &logger
    );
};

}// namespace leaf::abstract

#include "abstract/ini_configuration_loader.tcc"

#endif// LEAF_INI_CONFIGURATION_LOADER_HPP
