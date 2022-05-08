//
// Created by loicl on 7/8/2021.
//

#ifndef LEAF_SYNCED_COUT_HPP
#define LEAF_SYNCED_COUT_HPP

#include <iostream>

#include "stream/synced_stream.hpp"

namespace leaf::stream
{
constexpr static const _synced_stream synced_cout = _synced_stream<std::cout>();
}

#endif// LEAF_SYNCED_COUT_HPP
