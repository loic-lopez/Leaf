//
// Created by LoicL on 17/12/2020.
//

#ifndef LEAF_MIME_TYPE_HPP
#define LEAF_MIME_TYPE_HPP

#include <string>
#include <utility>
#include <vector>

namespace leaf::mime_type
{

struct MimeType
{
  const std::vector<std::string> extensions;
  const std::string type;

  MimeType(std::string type, std::vector<std::string> extensions) : extensions(std::move(extensions)), type(std::move(type)) {}

  ~MimeType() = default;
};

}// namespace leaf::mime_type

#endif// LEAF_MIME_TYPE_HPP
