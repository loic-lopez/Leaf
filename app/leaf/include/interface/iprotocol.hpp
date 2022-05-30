//
// Created by LoicL on 28/11/2020.
//

#ifndef LEAF_IPROTOCOL_HPP
#define LEAF_IPROTOCOL_HPP

namespace leaf::interface
{
class IProtocol
{
  protected:
    virtual void initializeContext() = 0;

  public:
    virtual void initialize() = 0;

    virtual ~IProtocol() = default;
};
}// namespace leaf::interface

#endif// LEAF_IPROTOCOL_HPP
