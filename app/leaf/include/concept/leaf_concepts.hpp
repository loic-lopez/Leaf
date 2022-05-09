//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_CONCEPTS_HPP
#define LEAF_CONCEPTS_HPP

#include <concepts>

#include "interface/iexception.hpp"

namespace leaf::concepts
{

template<class LeafException>
concept LeafExceptionClass = std::is_base_of_v<interface::IException, LeafException>;

}

#endif// LEAF_CONCEPTS_HPP
