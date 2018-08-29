#pragma once
#include <mutex>
#include "temp/core/container.h"
#include "temp/core/type.h"

namespace temp {

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
  static void Log(const char* tag, const char* msg, LogLevel level,
                  const char* file, int line);

  static void Log(const std::string& tag, const std::string& msg,
                  LogLevel level, const char* file, int line) {
    Log(tag.c_str(), msg.c_str(), level, file, line);
  }

  static void Log(const char* tag, const std::string& msg, LogLevel level,
                  const char* file, int line) {
    Log(tag, msg.c_str(), level, file, line);
  }

  static void Log(const std::string& tag, const char* msg, LogLevel level,
                  const char* file, int line) {
    Log(tag.c_str(), msg, level, file, line);
  }

  static void Log(const String& tag, const String& msg, LogLevel level,
                  const char* file, int line) {
    Log(tag.c_str(), msg.c_str(), level, file, line);
  }
  static void Log(const char* tag, const String& msg, LogLevel level,
                  const char* file, int line) {
    Log(tag, msg.c_str(), level, file, line);
  }

  static void Log(const String& tag, const char* msg, LogLevel level,
                  const char* file, int line) {
    Log(tag.c_str(), msg, level, file, line);
  }

  template <typename T, typename U>
  static void Trace(T tag, U msg, const char* file, int line) {
    Log(tag, msg, LogLevel::kTrace, file, line);
  }

  template <typename T, typename U>
  static void Debug(T tag, U msg, const char* file, int line) {
    Log(tag, msg, LogLevel::kDebug, file, line);
  }

  template <typename T, typename U>
  static void Info(T tag, U msg, const char* file, int line) {
    Log(tag, msg, LogLevel::kInfo, file, line);
  }

  template <typename T, typename U>
  static void Warn(T tag, U msg, const char* file, int line) {
    Log(tag, msg, LogLevel::kWarn, file, line);
  }

  template <typename T, typename U>
  static void Error(T tag, U msg, const char* file, int line) {
    Log(tag, msg, LogLevel::kError, file, line);
  }

  template <typename T, typename U>
  static void Fatal(T tag, U msg, const char* file, int line) {
    Log(tag, msg, LogLevel::kFatal, file, line);
  }

  LogLevel& level() { return level_; }

 private:
  mutable std::mutex mutex_;
  LogLevel level_ = LogLevel::kTrace;
};

}  // namespace temp

#define TEMP_LOG_TRACE(tag, msg) \
  ::temp::Logger::Trace(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_DEBUG(tag, msg) \
  ::temp::Logger::Debug(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_INFO(tag, msg) \
  ::temp::Logger::Info(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_WARN(tag, msg) \
  ::temp::Logger::Warn(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_ERROR(tag, msg) \
  ::temp::Logger::Error(tag, msg, __FILE__, __LINE__)
#define TEMP_LOG_FATAL(tag, msg) \
  ::temp::Logger::Fatal(tag, msg, __FILE__, __LINE__)