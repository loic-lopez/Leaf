//
// Created by LoicL on 05/12/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
#define LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP

#include <utility>
#include <source_location>
#include <boost/current_function.hpp>
#include "exceptions/ini_section_not_found.hpp"
#include "exceptions/ini_property_in_section_exception.hpp"

namespace Leaf::Abstracts {
    template<template<class> class stl_memory_container, class Model>
    template<Leaf::Concepts::LeafExceptionClass LeafException>
    boost::property_tree::ptree
    INIConfigurationLoader<stl_memory_container, Model>::initializeBoostPtree(const std::string &configFilePath) {
        if (!boost::filesystem::exists(configFilePath) || boost::filesystem::is_directory(configFilePath)) {
            BOOST_THROW_EXCEPTION(LeafException(configFilePath, errno, std::source_location::current()));
        }

        boost::property_tree::ptree pTree;

        boost::property_tree::ini_parser::read_ini(configFilePath, pTree);

        checkForPtreeIntegrity(pTree, configFilePath);

        return pTree;
    }

    template<template<class> class stl_memory_container, class Model>
    void INIConfigurationLoader<stl_memory_container, Model>::checkForPtreeIntegrity(
            const boost::property_tree::ptree &pTree,
            const std::string &configFilePath) {
        for (const auto &section : _sections) {
            if (pTree.find(section) == pTree.not_found()) {
                BOOST_THROW_EXCEPTION(Exceptions::IniSectionNotFound(section, configFilePath, std::source_location::current()));
            } else {
                /*auto propertyCount = pTree.find(section)->second.count("port");
                if (propertyCount == 0)
                    BOOST_THROW_EXCEPTION(
                        Exceptions::IniPropertyInSectionException(
                            Exceptions::IniPropertyInSectionException::MISSING,
                            "port",
                            section,
                            configFilePath,
                            std::source_location::current()
                        )
                    );
                else if (propertyCount > 1) {
                    BOOST_THROW_EXCEPTION(
                        Exceptions::IniPropertyInSectionException(
                            Exceptions::IniPropertyInSectionException::DUPLICATED,
                            "port",
                            section,
                            configFilePath,
                            std::source_location::current()
                        )
                    );
                    }
                    */
            }
        }
    }

    template<template<class> class stl_memory_container, class Model>
    INIConfigurationLoader<stl_memory_container, Model>::INIConfigurationLoader(std::vector<std::string> sections)
            : _sections(
            std::move(sections)) {

    }
}


#endif //LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
