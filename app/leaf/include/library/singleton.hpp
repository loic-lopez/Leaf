//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_SINGLETON_HPP
#define LEAF_SINGLETON_HPP

namespace leaf::library
{
template<typename T>
class Singleton
{
  public:
    inline static T &GetInstance()
    {
      static T instance;// load the first time
      return instance;  // destruction = end of the program
    }

    Singleton(const Singleton<T> &)             = delete;
    Singleton<T> &operator=(const Singleton<T>) = delete;
    Singleton<T> &operator=(Singleton<T> &&)    = delete;
    Singleton(Singleton<T> &&)                  = delete;

  protected:
    Singleton()          = default;
    virtual ~Singleton() = default;
};
}// namespace leaf::library

#endif// LEAF_SINGLETON_HPP
