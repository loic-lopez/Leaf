//
// Created by loicl on 7/17/2022.
//

#include "log/logger_factory.hpp"

#include <spdlog/cfg/argv.h>
#include <spdlog/cfg/env.h>

#include <iostream>

namespace leaf::log
{

void LoggerFactory::InitializeFactory()
{
  const auto processorCount = std::thread::hardware_concurrency();
  auto spdlogThreads        = processorCount / 4;
  if (spdlogThreads <= 0) spdlogThreads = 2;

  spdlog::cfg::load_env_levels();
  spdlog::init_thread_pool(8192, spdlogThreads);
  spdlog::flush_every(std::chrono::seconds(3));

  _stderrSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
  _stderrSink->set_pattern(ColorsLoggingPattern);

  _stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  _stdoutSink->set_pattern(ColorsLoggingPattern);
}

RotatingFileSink LoggerFactory::CreateRotatingFileSink(
  const boost::format &logFile, const std::size_t maxFileSize, const std::size_t maxFiles
)
{
  auto rotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
    logFile.str(), static_cast<std::size_t>(1024 * 1024) * maxFileSize /* conversion to MB */, maxFiles
  );
  rotatingFileSink->set_pattern(BasicLoggingPattern);

  return rotatingFileSink;
}

Logger LoggerFactory::CreateLogger(
  const std::string &loggerName, const std::vector<spdlog::sink_ptr> &sinks, const bool mustRegisterLogger = true
)
{
  auto logger = std::make_shared<spdlog::async_logger>(loggerName, sinks.begin(), sinks.end(), spdlog::thread_pool());

#ifndef NDEBUG
  logger->set_level(spdlog::level::trace);
#endif

  if (mustRegisterLogger) spdlog::register_logger(logger);
  return logger;
}

Logger LoggerFactory::BasicStdoutLogger(const std::string &loggerName)
{
  const std::vector<spdlog::sink_ptr> sinks {_stdoutSink};

  return CreateLogger(loggerName, sinks, false);
}

Logger LoggerFactory::BasicStderrLogger(const std::string &loggerName)
{
  const std::vector<spdlog::sink_ptr> sinks {_stderrSink};

  return CreateLogger(loggerName + "_stderr", sinks, false);
}

Logger LoggerFactory::CreateStdoutLogger(
  const std::string &loggerName, const boost::format &logFile, const std::size_t maxFileSize, const std::size_t maxFiles
)
{
  const std::vector<spdlog::sink_ptr> sinks {_stdoutSink, CreateRotatingFileSink(logFile, maxFileSize, maxFiles)};

  return CreateLogger(loggerName, sinks);
}

Logger LoggerFactory::CreateStderrLogger(
  const std::string &loggerName, const boost::format &logFile, const std::size_t maxFileSize, const std::size_t maxFiles
)
{
  const std::vector<spdlog::sink_ptr> sinks {_stderrSink, CreateRotatingFileSink(logFile, maxFileSize, maxFiles)};

  return CreateLogger(loggerName + "_stderr", sinks);
}

void LoggerFactory::Shutdown() { spdlog::shutdown(); }

Logger LoggerFactory::BasicStdoutLoggerWithoutFormatting(const std::string &loggerName) {
  auto logger = BasicStdoutLogger(loggerName);
  return logger;
}

}// namespace leaf::log
