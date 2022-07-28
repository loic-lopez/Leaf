//
// Created by loicl on 6/6/2022.
//

#include "exception/abstract/exception_with_exit_status.hpp"

namespace leaf::exception::abstract
{

ExceptionWithExitStatus::ExceptionWithExitStatus(const int exitCode) : _exitCode(exitCode) {}

}// namespace leaf::exception::abstract
