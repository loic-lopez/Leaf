//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_INI_CONFIGURATION_HPP
#define LEAF_INI_CONFIGURATION_HPP

#include <string>
#include <concepts>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem/operations.hpp>
#include "concepts/leaf_concepts.hpp"

namespace Leaf::Abstracts {

    class INIConfiguration {
    protected:
        template<Leaf::Concepts::LeafExceptionClass LeafException>
        boost::property_tree::ptree initializeBoostPtree(const std::string &configFilePath);


    public:
        virtual void initialize(const std::string &configFilePath) = 0;
    };
}

#include "abstracts/ini_configuration_templated_impl.hpp"

#endif //LEAF_INI_CONFIGURATION_HPP
