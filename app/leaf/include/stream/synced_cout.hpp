//
// Created by loicl on 7/8/2021.
//

#ifndef LEAF_SYNCED_COUT_HPP
#define LEAF_SYNCED_COUT_HPP

#include "stream/synced_stream.hpp"

#include <iostream>

namespace leaf::stream
{
constexpr static const _synced_stream synced_cout = _synced_stream<std::cout>();
}

#endif// LEAF_SYNCED_COUT_HPP
