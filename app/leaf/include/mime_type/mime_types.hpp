//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_MIME_TYPES_HPP
#define LEAF_MIME_TYPES_HPP

#include "mime_type/mime_type.hpp"

#include <vector>

namespace leaf::mime_type
{
struct MimeTypes
{
    const std::vector<MimeType> mimeTypes;

    constexpr static const char DEFAULT[] = "text/plain";

    [[nodiscard]] std::string extensionToType(const std::string &extension) const
    {
      for (const MimeType &mimeType : mimeTypes)
      {
        for (const std::string_view ext : mimeType.extensions)
        {
          if (ext == extension) { return mimeType.type; }
        }
      }

      return DEFAULT;
    }
};
}// namespace leaf::mime_type

#endif// LEAF_MIME_TYPES_HPP
