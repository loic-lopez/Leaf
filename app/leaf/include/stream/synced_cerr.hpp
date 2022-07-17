//
// Created by loicl on 7/8/2021.
//

#ifndef LEAF_SYNCED_CERR_HPP
#define LEAF_SYNCED_CERR_HPP

#include "stream/synced_stream.hpp"

#include <iostream>

namespace leaf::stream
{
constexpr static const _synced_stream synced_cerr = _synced_stream<std::cerr>();
}

#endif// LEAF_SYNCED_CERR_HPP
