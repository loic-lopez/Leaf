//
// Created by LoicL on 23/01/2021.
//

#ifndef __LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP__
#define __LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP__

#include "mime_type/mime_types.hpp"

#include <gtest/gtest.h>

namespace leaf::test
{
class LeafMimeTypesLoaderTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
      Test::SetUp();
      _mimeTypes = nullptr;
    }

  public:
    std::unique_ptr<mime_type::MimeTypes> _mimeTypes;
};
}// namespace leaf::test

#endif// __LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP__
