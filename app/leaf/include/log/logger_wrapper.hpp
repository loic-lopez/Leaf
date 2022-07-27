//
// Created by loicl on 7/27/2022.
//

#ifndef __LEAF_LOG_LOGGER_WRAPPER_HPP__
#define __LEAF_LOG_LOGGER_WRAPPER_HPP__

#include "log/logger_defines.hpp"

#include <spdlog/details/thread_pool.h>

#include <memory>
#include <utility>

namespace leaf::log
{
class LoggerWrapper : std::enable_shared_from_this<LoggerWrapper>
{
  public:
    explicit LoggerWrapper(
      std::shared_ptr<spdlog::details::thread_pool> loggerThreadPool, Logger logger, const std::string_view &loggerName
    )
        : _loggerThreadPool(std::move(loggerThreadPool)), _logger(std::move(logger)), _loggerName(loggerName)
    {
    }

    template<typename... Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) const
    {
      _logger->log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&...args) const
    {
      _logger->log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&...args) const
    {
      _logger->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) const
    {
      _logger->log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&...args) const
    {
      _logger->log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&...args) const
    {
      _logger->log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
    }

    template<typename T>
    void trace(const T &msg) const
    {
      _logger->log(spdlog::level::trace, msg);
    }

    template<typename T>
    void debug(const T &msg) const
    {
      _logger->log(spdlog::level::debug, msg);
    }

    template<typename T>
    void info(const T &msg) const
    {
      _logger->log(spdlog::level::info, msg);
    }

    template<typename T>
    void warn(const T &msg) const
    {
      _logger->log(spdlog::level::warn, msg);
    }

    template<typename T>
    void error(const T &msg) const
    {
      _logger->log(spdlog::level::err, msg);
    }

    template<typename T>
    void critical(const T &msg) const
    {
      _logger->log(spdlog::level::critical, msg);
    }

  private:
    const std::shared_ptr<spdlog::details::thread_pool> _loggerThreadPool;
    const Logger _logger;
    const std::string_view _loggerName;
};
}// namespace leaf::log

#endif// __LEAF_LOG_LOGGER_WRAPPER_HPP__
