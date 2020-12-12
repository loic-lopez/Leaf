//
// Created by LoicL on 06/12/2020.
//

#ifndef LEAF_ERROR_INFO_HPP
#define LEAF_ERROR_INFO_HPP

#include <boost/exception/error_info.hpp>

namespace Leaf::Exceptions::ErrorInfo {
    typedef boost::error_info<struct errinfo_server_config_file_path_, std::string> errinfo_server_config_file_path;
    typedef boost::error_info<struct errinfo_mime_types_config_file_path_, std::string> errinfo_mime_types_config_file_path;

}

#endif //LEAF_ERROR_INFO_HPP
