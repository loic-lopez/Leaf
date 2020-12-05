//
// Created by LoicL on 06/12/2020.
//

#ifndef LEAF_TYPE_DEFINES_HPP
#define LEAF_TYPE_DEFINES_HPP

#include <boost/exception/error_info.hpp>

namespace Leaf::Exceptions {
    namespace File {
        typedef boost::error_info<struct errinfo_config_file_, std::string> errinfo_config_file;
    }
}

#endif //LEAF_TYPE_DEFINES_HPP
