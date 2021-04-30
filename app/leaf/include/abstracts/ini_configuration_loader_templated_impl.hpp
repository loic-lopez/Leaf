//
// Created by LoicL on 05/12/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
#define LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP

#include <boost/current_function.hpp>
#include <utility>
#include "exceptions/ini_section_not_found.hpp"

namespace Leaf::Abstracts {
    template<class Model>
    template<Leaf::Concepts::LeafExceptionClass LeafException>
    boost::property_tree::ptree INIConfigurationLoader<Model>::initializeBoostPtree(const std::string &configFilePath) {
        if (!boost::filesystem::exists(configFilePath) || boost::filesystem::is_directory(configFilePath)) {
            BOOST_THROW_EXCEPTION(LeafException(configFilePath, BOOST_CURRENT_FUNCTION, __LINE__, errno));
        }

        boost::property_tree::ptree pTree;
        boost::property_tree::ini_parser::read_ini(configFilePath, pTree);

        checkForPtreeIntegrity(pTree, configFilePath);

        return pTree;
    }

    template<class Model>
    void INIConfigurationLoader<Model>::checkForPtreeIntegrity(const boost::property_tree::ptree &pTree,
                                                               const std::string &configFilePath) {
        for (const auto &section : _sections) {
            if (pTree.find(section) == pTree.not_found()) {
                boost::throw_exception(
                        Exceptions::IniSectionNotFound(section, configFilePath, BOOST_CURRENT_FUNCTION, __LINE__),
                        BOOST_CURRENT_LOCATION
                );
            }
        }
    }

    template<class Model>
    INIConfigurationLoader<Model>::INIConfigurationLoader(std::vector<std::string> sections): _sections(
            std::move(sections)) {

    }
}


#endif //LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
