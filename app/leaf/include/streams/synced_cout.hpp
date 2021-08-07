//
// Created by loicl on 7/8/2021.
//

#ifndef LEAF_SYNCED_COUT_HPP
#define LEAF_SYNCED_COUT_HPP

#include <iostream>
#include <syncstream>
#include <ostream>

namespace Leaf::Streams {
    class _synced_cout {
    public:
        template <class T>
        std::osyncstream operator<<(const T& value) const {
            std::osyncstream synced_cout_stream(std::cout);
            synced_cout_stream << value;
            return synced_cout_stream;
        }
    };

    inline static const _synced_cout synced_cout = _synced_cout();
}

#endif //LEAF_SYNCED_COUT_HPP
