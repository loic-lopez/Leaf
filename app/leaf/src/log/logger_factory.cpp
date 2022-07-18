//
// Created by loicl on 7/17/2022.
//

#include "log/logger_factory.hpp"

#include <spdlog/cfg/env.h>
#include <spdlog/cfg/argv.h>

#include <cstddef>

namespace leaf::log
{

void LoggerFactory::InitializeFactory()
{
  const auto processorCount = std::thread::hardware_concurrency();
  auto spdlogThreads        = processorCount / 4;
  if (spdlogThreads <= 0) spdlogThreads = 2;

  spdlog::init_thread_pool(8192, spdlogThreads);
  spdlog::cfg::load_env_levels();
  spdlog::flush_every(std::chrono::seconds(3));

  _stderrSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
  _stderrSink->set_pattern(ColorsLoggingPattern);

  _stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  _stdoutSink->set_pattern(ColorsLoggingPattern);
}

RotatingFileSink LoggerFactory::CreateRotatingFileSink(const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles)
{
  auto rotatingFileSink =
    std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFile.str(), static_cast<std::size_t>(1024 * 1024) * maxFileSize /* conversion to MB */, maxFiles);
  rotatingFileSink->set_pattern(BasicLoggingPattern);

  return rotatingFileSink;
}

Logger LoggerFactory::BasicStdoutLogger(const std::string &loggerName)
{
  std::vector<spdlog::sink_ptr> sinks {_stdoutSink};

  auto stdoutLogger = std::make_shared<spdlog::logger>(loggerName, sinks.begin(), sinks.end());
  return stdoutLogger;
}

Logger LoggerFactory::BasicStderrLogger(const std::string &loggerName)
{
  std::vector<spdlog::sink_ptr> sinks {_stderrSink};

  auto stderrLogger = std::make_shared<spdlog::logger>(loggerName + "_stderr", sinks.begin(), sinks.end());
  return stderrLogger;
}

Logger LoggerFactory::CreateStdoutLogger(const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles)
{
  std::vector<spdlog::sink_ptr> sinks {_stdoutSink, CreateRotatingFileSink(logFile, maxFileSize, maxFiles)};
  auto logger = std::make_shared<spdlog::async_logger>(loggerName, sinks.begin(), sinks.end(), spdlog::thread_pool());

  spdlog::register_logger(logger);
  return logger;
}

Logger LoggerFactory::CreateStderrLogger(const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles)
{
  std::vector<spdlog::sink_ptr> sinks {_stderrSink, CreateRotatingFileSink(logFile, maxFileSize, maxFiles)};
  auto logger = std::make_shared<spdlog::async_logger>(loggerName + "_stderr", sinks.begin(), sinks.end(), spdlog::thread_pool());

  spdlog::register_logger(logger);
  return logger;
}

void LoggerFactory::Shutdown()
{
  spdlog::shutdown();
}

}// namespace leaf::log
