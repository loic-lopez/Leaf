//
// Created by loicl on 7/8/2021.
//

#ifndef LEAF_SYNCED_CERR_HPP
#define LEAF_SYNCED_CERR_HPP

#include <iostream>
#include <syncstream>
#include <ostream>

namespace Leaf::Streams {
    class _synced_cerr {
    public:
        template <class T>
        std::osyncstream operator<<(const T& value) const {
            std::osyncstream synced_cout_stream(std::cerr);
            synced_cout_stream << value;
            return synced_cout_stream;
        }
    };

    inline static const _synced_cerr synced_cerr = _synced_cerr();
}

#endif //LEAF_SYNCED_CERR_HPP
