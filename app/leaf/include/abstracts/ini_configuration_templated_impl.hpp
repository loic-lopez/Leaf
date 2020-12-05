//
// Created by LoicL on 05/12/2020.
//

#ifndef LEAF_INI_CONFIGURATION_TEMPLATED_IMPL_HPP
#define LEAF_INI_CONFIGURATION_TEMPLATED_IMPL_HPP

#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/errinfo_at_line.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <boost/exception/errinfo_file_handle.hpp>
#include <boost/exception/errinfo_file_name.hpp>
#include <boost/exception/errinfo_file_open_mode.hpp>
#include <boost/current_function.hpp>
#define BOOST_STACKTRACE_USE_ADDR2LINE
#include <boost/stacktrace.hpp>
#include <iostream>

namespace Leaf::Abstracts {
    template<Leaf::Concepts::LeafExceptionClass LeafException>
    boost::property_tree::ptree INIConfiguration::initializeBoostPtree(const std::string &configFilePath) {
        if (!boost::filesystem::exists(configFilePath)) {
            boost::throw_exception(LeafException(configFilePath, BOOST_CURRENT_FUNCTION, __LINE__, errno), BOOST_CURRENT_LOCATION);
        }

        boost::property_tree::ptree pTree;
        boost::property_tree::ini_parser::read_ini(configFilePath, pTree);

        return pTree;
    }
}


#endif //LEAF_INI_CONFIGURATION_TEMPLATED_IMPL_HPP
