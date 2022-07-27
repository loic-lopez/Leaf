//
// Created by loicl on 7/17/2022.
//

#ifndef __LEAF_LOG_LOGGER_FACTORY_HPP__
#define __LEAF_LOG_LOGGER_FACTORY_HPP__

#include "log/logger_defines.hpp"
#include "log/logger_wrapper.hpp"

#include <boost/format.hpp>

#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string_view>

namespace leaf::log
{

using std::string_view_literals::operator""sv;

class LoggerFactory
{
  public:
    // constructors
    LoggerFactory(const LoggerFactory &)          = delete;
    LoggerFactory &operator=(const LoggerFactory) = delete;
    LoggerFactory(LoggerFactory &&)               = delete;
    LoggerFactory &operator=(LoggerFactory &&)    = delete;
    LoggerFactory()                               = delete;

    static void InitializeFactory();
    static void ShutdownGlobalThreadPool();

    static LoggerWrapperPtr BasicStdoutLogger(const std::string &loggerName);
    static LoggerWrapperPtr BasicStderrLogger(const std::string &loggerName);

    static StandardLoggers CreateStdLoggers(
      const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles,
      std::size_t leafLogThreadsPerLeafServer
    );
    static StandardLoggers CreateStdLoggers(
      const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles
    );

  private:
    inline static const std::string ColorsLoggingPattern = "[%H:%M:%S %T] [thread %t] [%n] [%^%l%$] %v";
    inline static const std::string BasicLoggingPattern  = "[%H:%M:%S %T] [thread %t] [%n] [%l] %v";
    inline static StderrSink _stderrSink;
    inline static StdoutSink _stdoutSink;

    static RotatingFileSink CreateRotatingFileSink(const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles);
    static LoggerWrapperPtr CreateLogger(
      const std::string &loggerName, const std::vector<spdlog::sink_ptr> &sinks, const ThreadPool &threadPool, bool mustRegisterLogger
    );

    static LoggerWrapperPtr CreateStdoutLogger(
      const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles,
      const ThreadPool &threadPool
    );
    static LoggerWrapperPtr CreateStderrLogger(
      const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles,
      const ThreadPool &threadPool
    );
};

}// namespace leaf::log

#endif// __LEAF_LOG_LOGGER_FACTORY_HPP__
