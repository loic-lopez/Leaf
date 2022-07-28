//
// Created by loicl on 6/6/2022.
//

#ifndef __LEAF_EXCEPTION_EXIT_TO_MAIN_HPP__
#define __LEAF_EXCEPTION_EXIT_TO_MAIN_HPP__

#include "exception/abstract/exception_with_exit_status.hpp"

namespace leaf::exception
{

class LeafExceptionWithExitStatus : public abstract::ExceptionWithExitStatus
{
  public:
    using abstract::ExceptionWithExitStatus::ExceptionWithExitStatus;
};

}// namespace leaf::exception

#endif// __LEAF_EXCEPTION_EXIT_TO_MAIN_HPP__
