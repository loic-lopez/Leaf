//
// Created by LoicL on 23/01/2021.
//

#ifndef LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP
#define LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP

#include <gtest/gtest.h>

#include "mime_type/mime_types.hpp"

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

#endif// LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP
