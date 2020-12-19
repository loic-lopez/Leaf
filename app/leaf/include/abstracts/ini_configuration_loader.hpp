//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_HPP
#define LEAF_INI_CONFIGURATION_LOADER_HPP

#include <string>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem/operations.hpp>
#include "concepts/leaf_concepts.hpp"

namespace Leaf::Abstracts {

    template<class Model>
    class INIConfigurationLoader {
    protected:
        template<Leaf::Concepts::LeafExceptionClass LeafException>
        boost::property_tree::ptree initializeBoostPtree(const std::string &configFilePath);

    public:
        virtual Model load(const std::string &configFilePath) = 0;
    };
}

#include "abstracts/ini_configuration_loader_templated_impl.hpp"

#endif //LEAF_INI_CONFIGURATION_LOADER_HPP
