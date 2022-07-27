//
// Created by LoicL on 28/11/2020.
//

#ifndef __LEAF_IPROTOCOL_HPP__
#define __LEAF_IPROTOCOL_HPP__

namespace leaf::interface
{
class IProtocol
{
  public:
    virtual void initialize() = 0;
    virtual ~IProtocol()      = default;

  protected:
    virtual void initializeContext() = 0;
};
}// namespace leaf::interface

#endif// __LEAF_IPROTOCOL_HPP__
