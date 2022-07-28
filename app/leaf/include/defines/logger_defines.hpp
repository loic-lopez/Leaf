//
// Created by loicl on 7/18/2022.
//

#ifndef __LEAF_DEFINES_LOGGER_DEFINES_HPP__
#define __LEAF_DEFINES_LOGGER_DEFINES_HPP__

#include <spdlog/async_logger.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace leaf
{

namespace log
{
class LoggerWrapper;
}// namespace log

namespace defines::log
{
using Logger           = std::shared_ptr<spdlog::logger>;
using RotatingFileSink = std::shared_ptr<spdlog::sinks::rotating_file_sink_mt>;
using StderrSink       = std::shared_ptr<spdlog::sinks::stderr_color_sink_mt>;
using StdoutSink       = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>;
using LoggerWrapperPtr = std::shared_ptr<::leaf::log::LoggerWrapper>;
using ThreadPool       = std::shared_ptr<spdlog::details::thread_pool>;
}// namespace defines::log

}// namespace leaf

#endif// __LEAF_DEFINES_LOGGER_DEFINES_HPP__
