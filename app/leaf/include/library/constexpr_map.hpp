//
// Created by loicl on 5/30/2022.
//

#ifndef CONSTEXPR_MAP_HPP
#define CONSTEXPR_MAP_HPP

#include <algorithm>
#include <array>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace leaf::library
{

template<class Key, class Value, std::size_t Size>
class ConstexprMap
{
    using DataContainer     = std::array<std::pair<Key, Value>, Size>;
    using DataIterator      = typename DataContainer::iterator;
    using DataConstIterator = typename DataContainer::const_iterator;

  public:
    [[nodiscard]] constexpr DataConstIterator end() const { return std::end(data); }

    [[nodiscard]] constexpr DataConstIterator begin() const { return std::begin(data); }

    [[nodiscard]] constexpr DataConstIterator at(const Key &key) const
    {
      const auto endItr = end();

      if (const auto itr = std::find_if(begin(), endItr, [&key](const auto &v) { return v.first == key; }); itr != endItr) return itr;

      return endItr;
    }

    constexpr ConstexprMap(std::initializer_list<std::pair<Key, Value>> list) : data {BuildContainer(list)} {}

  private:
    std::array<std::pair<Key, Value>, Size> data;

    static constexpr std::array<std::pair<Key, Value>, Size> BuildContainer(std::initializer_list<std::pair<Key, Value>> list)
    {
      std::array<std::pair<Key, Value>, Size> dataContainer;

      int i = 0;
      for (const auto &listValue : list)
      {
        dataContainer[i] = listValue;
        i++;
      }

      return dataContainer;
    }
};

}// namespace leaf::library

#endif// CONSTEXPR_MAP_HPP
