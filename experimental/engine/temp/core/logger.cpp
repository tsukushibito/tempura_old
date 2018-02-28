#include <iostream>

#include "temp/core/logger.h"

namespace temp {
namespace core {

void Logger::log(const String &tag, const String &msg, LogLevel level) {
  if (level < getInstance().level_) return;
  String levelTag;
  switch (level) {
    case LogLevel::kTrace:
      levelTag = "[TRACE]";
      break;
    case LogLevel::kDebug:
      levelTag = "[DEBUG]";
      break;
    case LogLevel::kInfo:
      levelTag = "[INFO]";
      break;
    case LogLevel::kWarn:
      levelTag = "[WARN]";
      break;
    case LogLevel::kError:
      levelTag = "[ERROR]";
      break;
    case LogLevel::kFatal:
      levelTag = "[FATAL]";
      break;
    default:
      break;
  }
  std::cout << levelTag << "[" << tag << "] " << msg << std::endl;
}

void Logger::trace(const String &tag, const String &msg) {
  Logger::log(tag, msg, LogLevel::kTrace);
}

void Logger::debug(const String &tag, const String &msg) {
  Logger::log(tag, msg, LogLevel::kDebug);
}

void Logger::info(const String &tag, const String &msg) {
  Logger::log(tag, msg, LogLevel::kInfo);
}

void Logger::warn(const String &tag, const String &msg) {
  Logger::log(tag, msg, LogLevel::kWarn);
}

void Logger::error(const String &tag, const String &msg) {
  Logger::log(tag, msg, LogLevel::kError);
}

void Logger::fatal(const String &tag, const String &msg) {
  Logger::log(tag, msg, LogLevel::kFatal);
}

LogLevel Logger::getLevel() const {
  std::unique_lock<std::mutex> lock(mutex_);
  return level_;
}

void Logger::setLevel(LogLevel level) {
  std::unique_lock<std::mutex> lock(mutex_);
  level_ = level;
}

}  // namespace core
}  // namespace temp