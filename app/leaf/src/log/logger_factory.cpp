//
// Created by loicl on 7/17/2022.
//

#include "log/logger_factory.hpp"

#include <spdlog/cfg/argv.h>
#include <spdlog/cfg/env.h>

#include <iostream>
#include <vector>

namespace leaf::log
{

static constinit const std::size_t threadPoolQueueSize = 8192;

void LoggerFactory::InitializeFactory()
{
  spdlog::cfg::load_env_levels();
  spdlog::init_thread_pool(threadPoolQueueSize, 1);// init basic default global thread pool
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

LoggerWrapperPtr LoggerFactory::CreateLogger(
  const std::string &loggerName, const std::vector<spdlog::sink_ptr> &sinks, const ThreadPool &threadPool, bool mustRegisterLogger = true
)
{
  auto logger = std::make_shared<spdlog::async_logger>(loggerName, sinks.begin(), sinks.end(), threadPool);

#ifndef NDEBUG
  logger->set_level(spdlog::level::trace);
#endif

  if (mustRegisterLogger) spdlog::register_logger(logger);
  return std::make_shared<LoggerWrapper>(threadPool, logger, loggerName);
}

LoggerWrapperPtr LoggerFactory::BasicStdoutLogger(const std::string &loggerName)
{
  const std::vector<spdlog::sink_ptr> sinks {_stdoutSink};

  return CreateLogger(loggerName, sinks, spdlog::thread_pool(), false);
}

LoggerWrapperPtr LoggerFactory::BasicStderrLogger(const std::string &loggerName)
{
  const std::vector<spdlog::sink_ptr> sinks {_stderrSink};

  return CreateLogger(loggerName + "_stderr", sinks, spdlog::thread_pool(), false);
}

LoggerWrapperPtr LoggerFactory::CreateStdoutLogger(
  const std::string &loggerName, const boost::format &logFile, const std::size_t maxFileSize, const std::size_t maxFiles,
  const ThreadPool &threadPool
)
{
  const std::vector<spdlog::sink_ptr> sinks {_stdoutSink, CreateRotatingFileSink(logFile, maxFileSize, maxFiles)};

  return CreateLogger(loggerName, sinks, threadPool);
}

LoggerWrapperPtr LoggerFactory::CreateStderrLogger(
  const std::string &loggerName, const boost::format &logFile, const std::size_t maxFileSize, const std::size_t maxFiles,
  const ThreadPool &threadPool
)
{
  const std::vector<spdlog::sink_ptr> sinks {_stderrSink, CreateRotatingFileSink(logFile, maxFileSize, maxFiles)};

  return CreateLogger(loggerName + "_stderr", sinks, threadPool);
}

void LoggerFactory::ShutdownGlobalThreadPool() { spdlog::shutdown(); }

StandardLoggers LoggerFactory::CreateStdLoggers(
  const std::string &loggerName, const boost::format &logFile, const std::size_t maxFileSize, const std::size_t maxFiles,
  const std::size_t leafLogThreadsPerLeafServer
)
{
  StandardLoggers standardLoggers;
  auto threadPool              = std::make_shared<spdlog::details::thread_pool>(threadPoolQueueSize, leafLogThreadsPerLeafServer);
  standardLoggers.stdoutLogger = CreateStdoutLogger(loggerName, logFile, maxFileSize, maxFiles, threadPool);
  standardLoggers.stderrLogger = CreateStderrLogger(loggerName, logFile, maxFileSize, maxFiles, threadPool);

  return standardLoggers;
}

StandardLoggers LoggerFactory::CreateStdLoggers(
  const std::string &loggerName, const boost::format &logFile, const std::size_t maxFileSize, const std::size_t maxFiles
)
{
  StandardLoggers standardLoggers;
  auto threadPool              = spdlog::thread_pool();
  standardLoggers.stdoutLogger = CreateStdoutLogger(loggerName, logFile, maxFileSize, maxFiles, threadPool);
  standardLoggers.stderrLogger = CreateStderrLogger(loggerName, logFile, maxFileSize, maxFiles, threadPool);

  return standardLoggers;
}

}// namespace leaf::log
