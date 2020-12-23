//
// Created by LoicL on 23/01/2021.
//

#ifndef LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP
#define LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP

#include <gtest/gtest.h>
#include "models/mime_types.hpp"

namespace Leaf::Tests {
    class LeafMimeTypesLoaderTest : public ::testing::Test {
    protected:
        void SetUp() override {
            Test::SetUp();
            _mimeTypes = nullptr;
        }

        void TearDown() override {
            Test::TearDown();
            if (_mimeTypes != nullptr) {
                delete _mimeTypes;
            }
        }

    public:
        Leaf::Models::MimeTypes *_mimeTypes;
    };
}

#endif //LEAF_LEAF_MIME_TYPES_LOADER_TEST_HPP
