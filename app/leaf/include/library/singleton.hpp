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
    static T &Instance()
    {
      static T instance;// load the first time // C++11
      return instance;  // destruction = end of the program
    }

    // C++11, here no copy and move
    Singleton<T>(const Singleton &) = delete;

    Singleton<T> &operator=(const Singleton) = delete;

    Singleton<T>(Singleton &&) = delete;

    Singleton<T> &operator=(Singleton &&) = delete;

  protected:
    Singleton() = default;

    virtual ~Singleton() = default;
};
}// namespace leaf::library

#endif// LEAF_SINGLETON_HPP
