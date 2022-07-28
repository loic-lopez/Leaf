//
// Created by loicl on 7/28/2022.
//

#ifndef __LEAF_LOG_STANDARD_LOGGERS_HPP__
#define __LEAF_LOG_STANDARD_LOGGERS_HPP__

#include "defines/logger_defines.hpp"

namespace leaf::log
{
struct StandardLoggers
{
    defines::log::LoggerWrapperPtr stdoutLogger;
    defines::log::LoggerWrapperPtr stderrLogger;
};
}// namespace leaf::log

#endif// __LEAF_LOG_STANDARD_LOGGERS_HPP__
