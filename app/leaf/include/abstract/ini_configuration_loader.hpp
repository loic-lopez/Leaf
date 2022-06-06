//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_HPP
#define LEAF_INI_CONFIGURATION_LOADER_HPP

#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "concept/leaf_concepts.hpp"

namespace leaf::abstract
{

template<template<class> class stl_memory_container, class Model>
class INIConfigurationLoader
{
  public:
    virtual stl_memory_container<Model> load(const std::string &configFilePath) = 0;
    virtual ~INIConfigurationLoader()                                           = default;

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
    virtual void checkForPtreeIntegrity(const boost::property_tree::ptree &pTree, const std::string &configFilePath);
};

}// namespace leaf::abstract

#include "abstract/ini_configuration_loader.tcc"

#endif// LEAF_INI_CONFIGURATION_LOADER_HPP
