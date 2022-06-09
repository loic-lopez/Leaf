//
// Created by loicl on 6/6/2022.
//

#ifndef __LEAF_ABSTRACT_EXCEPTION_WITH_EXIT_STATUS_HPP__
#define __LEAF_ABSTRACT_EXCEPTION_WITH_EXIT_STATUS_HPP__

#include "interface/iexception.hpp"

namespace leaf::exception::abstract
{

class ExceptionWithExitStatus : public interface::IException
{
  public:
    explicit ExceptionWithExitStatus(int exitCode);

    int getExitCode() const { return _exitCode; }

  private:
    const int _exitCode;

    const char *what() const noexcept override { return nullptr; }
};

}// namespace leaf::exception::abstract

#endif// __LEAF_ABSTRACT_EXCEPTION_WITH_EXIT_STATUS_HPP__
