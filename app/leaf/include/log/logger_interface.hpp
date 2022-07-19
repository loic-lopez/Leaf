//
// Created by loicl on 7/18/2022.
//

#ifndef __LEAF_LOG_LOGGER_HPP__
#define __LEAF_LOG_LOGGER_HPP__

#include "log/logger_defines.hpp"

#include <regex>
#include <string>
#include <utility>

namespace leaf::log
{
class LoggerInterface
{
  public:
    // constructors
    LoggerInterface(const LoggerInterface &)          = delete;
    LoggerInterface &operator=(const LoggerInterface) = delete;
    LoggerInterface(LoggerInterface &&)               = delete;
    LoggerInterface &operator=(LoggerInterface &&)    = delete;

    explicit LoggerInterface(const std::string &loggerName) : _loggerName(ToSnakeCase(loggerName)) {}

  protected:
    Logger _stdout;
    Logger _stderr;
    std::string _loggerName;
    virtual ~LoggerInterface() = default;

  private:
    static std::string ToSnakeCase(const std::string_view &str)
    {
      const std::regex captureClassName(R"((?!\:\:)\w+(?=\())");
      const auto match = std::regex_iterator(str.begin(), str.end(), captureClassName);

      const std::string className(match->str());
      std::string snakeCaseStr;
      snakeCaseStr.reserve(className.size());

      int i = 0;
      for (const unsigned char c : className)
      {
        // Converting space to underscore
        if (i != 0 && static_cast<bool>(std::isupper(c))) snakeCaseStr += '_';

        snakeCaseStr += static_cast<char>(std::tolower(c));
        i++;
      }
      return snakeCaseStr;
    }
};
}// namespace leaf::log

#endif// __LEAF_LOG_LOGGER_HPP__
