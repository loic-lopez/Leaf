//
// Created by loicl on 7/18/2022.
//

#ifndef __LEAF_LOG_LOGGER_DEFINES_HPP__
#define __LEAF_LOG_LOGGER_DEFINES_HPP__

#include <spdlog/logger.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace leaf::log
{

using Logger           = std::shared_ptr<spdlog::logger>;
using RotatingFileSink = std::shared_ptr<spdlog::sinks::rotating_file_sink_mt>;
using StderrSink       = std::shared_ptr<spdlog::sinks::stderr_color_sink_mt>;
using StdoutSink       = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>;

}// namespace leaf::log

#endif// __LEAF_LOG_LOGGER_DEFINES_HPP__
