//
// Created by LoicL on 05/12/2020.
//

#ifndef LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
#define LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP

#include <boost/current_function.hpp>

namespace Leaf::Abstracts {
    template<Leaf::Concepts::LeafExceptionClass LeafException>
    boost::property_tree::ptree INIConfigurationLoader::initializeBoostPtree(const std::string &configFilePath) {
        if (!boost::filesystem::exists(configFilePath)) {
            boost::throw_exception(
                    LeafException(configFilePath, BOOST_CURRENT_FUNCTION, __LINE__, errno), BOOST_CURRENT_LOCATION
            );
        }

        boost::property_tree::ptree pTree;
        boost::property_tree::ini_parser::read_ini(configFilePath, pTree);

        return pTree;
    }
}


#endif //LEAF_INI_CONFIGURATION_LOADER_TEMPLATED_IMPL_HPP
