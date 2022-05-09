//
// Created by LoicL on 06/12/2020.
//

#ifndef LEAF_ERROR_INFO_HPP
#define LEAF_ERROR_INFO_HPP

#include <string>

#include <boost/exception/error_info.hpp>

namespace leaf::exception::error_info
{
using errinfo_server_config_file_path     = boost::error_info<struct errinfo_server_config_file_path_, std::string>;
using errinfo_mime_types_config_file_path = boost::error_info<struct errinfo_mime_types_config_file_path_, std::string>;
using errinfo_ini_section                 = boost::error_info<struct errinfo_ini_section_, std::string>;
using errinfo_ini_property_in_section     = boost::error_info<struct errinfo_ini_property_in_section_, std::string>;
}// namespace leaf::exception::error_info

#endif// LEAF_ERROR_INFO_HPP
