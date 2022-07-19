//
// Created by loicl on 7/17/2022.
//

#ifndef __LEAF_LOG_LOGGER_FACTORY_HPP__
#define __LEAF_LOG_LOGGER_FACTORY_HPP__

#include "log/logger_defines.hpp"

#include <boost/format.hpp>

#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string_view>

namespace leaf::log
{

using namespace std::string_view_literals;

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
    static void Shutdown();

    static Logger BasicStdoutLogger(const std::string &loggerName);
    static Logger BasicStderrLogger(const std::string &loggerName);
    static Logger CreateStdoutLogger(
      const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles
    );
    static Logger CreateStderrLogger(
      const std::string &loggerName, const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles
    );

  private:
    inline static const std::string ColorsLoggingPattern = "[%H:%M:%S %T] [thread %t] [%n] [%^%l%$] %v";
    inline static const std::string BasicLoggingPattern  = "[%H:%M:%S %T] [thread %t] [%n] [%l] %v";
    inline static StderrSink _stderrSink;
    inline static StdoutSink _stdoutSink;

    static RotatingFileSink CreateRotatingFileSink(const boost::format &logFile, std::size_t maxFileSize, std::size_t maxFiles);
    static Logger CreateLogger(const std::string &loggerName, const std::vector<spdlog::sink_ptr> &sinks, bool mustRegisterLogger);
};

}// namespace leaf::log

#endif// __LEAF_LOG_LOGGER_FACTORY_HPP__
