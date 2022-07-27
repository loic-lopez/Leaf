//
// Created by loicl on 7/18/2022.
//

#ifndef __LEAF_LOG_LOGGER_DEFINES_HPP__
#define __LEAF_LOG_LOGGER_DEFINES_HPP__

#include <spdlog/async_logger.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace leaf::log
{

class LoggerWrapper;

using Logger           = std::shared_ptr<spdlog::logger>;
using RotatingFileSink = std::shared_ptr<spdlog::sinks::rotating_file_sink_mt>;
using StderrSink       = std::shared_ptr<spdlog::sinks::stderr_color_sink_mt>;
using StdoutSink       = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>;
using LoggerWrapperPtr = std::shared_ptr<LoggerWrapper>;
using ThreadPool       = std::shared_ptr<spdlog::details::thread_pool>;

enum class ThreadPoolType : unsigned short
{
  GLOBAL,
  PER_LOGGER
};

struct StandardLoggers
{
    LoggerWrapperPtr stdoutLogger;
    LoggerWrapperPtr stderrLogger;
};

}// namespace leaf::log

#endif// __LEAF_LOG_LOGGER_DEFINES_HPP__
