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
  static void log(const String& tag, const String& msg, LogLevel level,
                  const char* file, int line);
  static void trace(const String& tag, const String& msg, const char* file,
                    int line);
  static void debug(const String& tag, const String& msg, const char* file,
                    int line);
  static void info(const String& tag, const String& msg, const char* file,
                   int line);
  static void warn(const String& tag, const String& msg, const char* file,
                   int line);
  static void error(const String& tag, const String& msg, const char* file,
                    int line);
  static void fatal(const String& tag, const String& msg, const char* file,
                    int line);

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