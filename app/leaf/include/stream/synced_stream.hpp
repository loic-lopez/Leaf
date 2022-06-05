//
// Created by loicl on 5/7/2022.
//

#ifndef LEAF_SYNCED_STREAM_HPP
#define LEAF_SYNCED_STREAM_HPP

#include <ostream>
#include <syncstream>

namespace leaf::stream
{
template<std::ostream &stream>
class _synced_stream
{
  public:
    template<class T>
    std::osyncstream operator<<(const T &value) const
    {
      std::osyncstream syncedStream(stream);
      syncedStream << value;
      return syncedStream;
    }
};
}// namespace leaf::stream

#endif// LEAF_SYNCED_STREAM_HPP
