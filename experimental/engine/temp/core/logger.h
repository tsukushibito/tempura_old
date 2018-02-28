#pragma once
#include <mutex>
#include "temp/common/container.h"
#include "temp/common/define.h"
#include "temp/common/type.h"

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
  static void log(const String &tag, const String &msg, LogLevel level);
  static void trace(const String &tag, const String &msg);
  static void debug(const String &tag, const String &msg);
  static void info(const String &tag, const String &msg);
  static void warn(const String &tag, const String &msg);
  static void error(const String &tag, const String &msg);
  static void fatal(const String &tag, const String &msg);

  LogLevel getLevel() const;
  void setLevel(LogLevel level);

 private:
  mutable std::mutex mutex_;
  LogLevel level_ = LogLevel::kTrace;
};

}  // namespace core
}  // namespace temp