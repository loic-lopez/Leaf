//
// Created by LoicL on 29/11/2020.
//

#ifndef __LEAF_CONCEPTS_HPP__
#define __LEAF_CONCEPTS_HPP__

#include "interface/iexception.hpp"

#include <concepts>

namespace leaf::concepts
{

template<class LeafException>
concept LeafExceptionClass = std::is_base_of_v<interface::IException, LeafException>;

}

#endif// __LEAF_CONCEPTS_HPP__
