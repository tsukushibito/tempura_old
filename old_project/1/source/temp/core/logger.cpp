#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "temp/core/logger.h"

namespace temp {
namespace core {

void Logger::log(const char *tag, const char *msg, LogLevel level,
                 const char *file, int line) {
  if (level < getInstance().level_) return;
  auto now = std::chrono::system_clock::now();
  auto now_time = std::chrono::system_clock::to_time_t(now);
  StringStream time_tag_stream;
  tm local_now;
#if defined(TEMP_PLATFORM_WINDOWS)
  localtime_s(&local_now, &now_time);
#elif defined(TEMP_PLATFORM_MAC)
  localtime_r(&now_time, &local_now);
#endif
  time_tag_stream << "[" << std::put_time(&local_now, "%Y-%m-%d %X") << "]";
  String time_tag = time_tag_stream.str();

  String level_tag;
  switch (level) {
    case LogLevel::kTrace:
      level_tag = "[TRACE]";
      break;
    case LogLevel::kDebug:
      level_tag = "[DEBUG]";
      break;
    case LogLevel::kInfo:
      level_tag = "[INFO]";
      break;
    case LogLevel::kWarn:
      level_tag = "[WARN]";
      break;
    case LogLevel::kError:
      level_tag = "[ERROR]";
      break;
    case LogLevel::kFatal:
      level_tag = "[FATAL]";
      break;
    default:
      break;
  }
#ifdef TEMP_LOG_FILE_AND_LINE
  std::cout << time_tag << level_tag << "[" << tag << "] " << msg << " : "
            << file << " : " << line << std::endl;
#else
  (void)file;
  (void)(Size)line;
  std::cout << time_tag << level_tag << "[" << tag << "] " << msg << std::endl;
#endif
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
