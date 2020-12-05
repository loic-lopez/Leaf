//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_CONCEPTS_HPP
#define LEAF_CONCEPTS_HPP

#include <concepts>
#include "interfaces/iexception.hpp"

namespace Leaf::Concepts {

    template<class LeafException>
    concept LeafExceptionClass = std::is_base_of<Interfaces::IException, LeafException>::value;

}

#endif //LEAF_CONCEPTS_HPP
