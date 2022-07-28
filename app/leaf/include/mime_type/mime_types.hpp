//
// Created by LoicL on 24/12/2020.
//

#ifndef __LEAF_MIME_TYPES_HPP__
#define __LEAF_MIME_TYPES_HPP__

#include "mime_type/mime_type.hpp"

#include <vector>

namespace leaf::mime_type
{

namespace defaults
{
using std::string_view_literals::operator""sv;
inline static constinit const std::string_view DEFAULT = "text/plain"sv;
}// namespace defaults

struct MimeTypes
{
    const std::vector<MimeType> mimeTypes;

    [[nodiscard]] std::string extensionToType(const std::string &extension) const
    {
      for (const MimeType &mimeType : mimeTypes)
      {
        for (const std::string_view ext : mimeType.extensions)
        {
          if (ext == extension) { return mimeType.type; }
        }
      }

      return defaults::DEFAULT.data();
    }
};
}// namespace leaf::mime_type

#endif// __LEAF_MIME_TYPES_HPP__
