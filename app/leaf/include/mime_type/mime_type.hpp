//
// Created by LoicL on 17/12/2020.
//

#ifndef __LEAF_MIME_TYPE_HPP__
#define __LEAF_MIME_TYPE_HPP__

#include <string>
#include <utility>
#include <vector>

namespace leaf::mime_type
{

struct MimeType
{
    const std::vector<std::string> extensions;
    const std::string type;

    explicit MimeType(std::string type, std::vector<std::string> extensions) : extensions(std::move(extensions)), type(std::move(type)) {}
};

}// namespace leaf::mime_type

#endif// __LEAF_MIME_TYPE_HPP__
