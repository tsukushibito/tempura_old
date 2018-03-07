#pragma once
#include <mutex>
#include "temp/common/common.h"

namespace temp {
namespace core {

enum class LogLevel {
  kTrace,
  kDebug,
  kInfo,
  kWarn,
  kError,
  kFatal,
};

class Logger : public Singleton<Logger> {
 public:
  static void log(const char* tag, const char* msg, LogLevel level,
                  const char* file, int line);

  static void log(const std::string& tag, const std::string& msg,
                  LogLevel level, const char* file, int line) {
    log(tag.c_str(), msg.c_str(), level, file, line);
  }

  static void log(const char* tag, const std::string& msg, LogLevel level,
                  const char* file, int line) {
    log(tag, msg.c_str(), level, file, line);
  }

  static void log(const std::string& tag, const char* msg, LogLevel level,
                  const char* file, int line) {
    log(tag.c_str(), msg, level, file, line);
  }

  static void log(const String& tag, const String& msg, LogLevel level,
                  const char* file, int line) {
    log(tag.c_str(), msg.c_str(), level, file, line);
  }
  static void log(const char* tag, const String& msg, LogLevel level,
                  const char* file, int line) {
    log(tag, msg.c_str(), level, file, line);
  }

  static void log(const String& tag, const char* msg, LogLevel level,
                  const char* file, int line) {
    log(tag.c_str(), msg, level, file, line);
  }

  template <typename T, typename U>
  static void trace(T tag, U msg, const char* file, int line) {
    log(tag, msg, LogLevel::kTrace, file, line);
  }

  template <typename T, typename U>
  static void debug(T tag, U msg, const char* file, int line) {
    log(tag, msg, LogLevel::kDebug, file, line);
  }

  template <typename T, typename U>
  static void info(T tag, U msg, const char* file, int line) {
    log(tag, msg, LogLevel::kInfo, file, line);
  }

  template <typename T, typename U>
  static void warn(T tag, U msg, const char* file, int line) {
    log(tag, msg, LogLevel::kWarn, file, line);
  }

  template <typename T, typename U>
  static void error(T tag, U msg, const char* file, int line) {
    log(tag, msg, LogLevel::kError, file, line);
  }

  template <typename T, typename U>
  static void fatal(T tag, U msg, const char* file, int line) {
    log(tag, msg, LogLevel::kFatal, file, line);
  }

  LogLevel getLevel() const;
  void setLevel(LogLevel level);

 private:
  mutable std::mutex mutex_;
  LogLevel level_ = LogLevel::kTrace;
};

}  // namespace core
}  // namespace temp

#define TEMP_LOG_TRACE(tag, msg) \
  ::temp::core::Logger::trace(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_DEBUG(tag, msg) \
  ::temp::core::Logger::debug(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_INFO(tag, msg) \
  ::temp::core::Logger::info(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_WARN(tag, msg) \
  ::temp::core::Logger::warn(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_ERROR(tag, msg) \
  ::temp::core::Logger::error(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_FATAL(tag, msg) \
  ::temp::core::Logger::fatal(tag, msg, __FILE__, __LINE__)