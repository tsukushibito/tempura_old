﻿/**
 * @file Logger.h
 * @brief logger class
 * @author tsukushibito
 * @version 0.0.1
 * @date 2015-09-17
 */
#pragma once
#ifndef GUARD_325c251321394362a453f269833195ae
#define GUARD_325c251321394362a453f269833195ae

#include "temp/defines.h"
#ifdef TEMP_PLATFORM_WINDOWS
#pragma warning(push)
#pragma warning(disable : 4244)
#endif
#include <spdlog.h>
#ifdef TEMP_PLATFORM_WINDOWS
#pragma warning(pop)
#endif
#include "temp/type.h"

namespace temp {
namespace system {

enum class LogLevel {
    Trace = spdlog::level::trace,
    Debug = spdlog::level::debug,
    Info = spdlog::level::info,
    Notice = spdlog::level::notice,
    Warn = spdlog::level::warn,
    Error = spdlog::level::err,
    Critical = spdlog::level::critical,
    Alert = spdlog::level::alert,
    Emerg = spdlog::level::emerg,
};

template < typename LoggerCreatorType >
class Logger : temp::Uncopyable {
private:
    Logger() {
        spLogger_ = LoggerCreatorType::create();
        spLogger_->set_level(spdlog::level::trace);
    }

    ~Logger() = default;

public:
    static void initialize() {
        pInstance = new Logger;
#ifdef TEMP_PLATFORM_WINDOWS
        default_rdbuf = std::cout.rdbuf(&dsb);
#endif
    }

    static void terminate() {
#ifdef TEMP_PLATFORM_WINDOWS
        std::cout.rdbuf(default_rdbuf);
#endif
        delete pInstance;
    }

    template < typename... Args >
    static void trace(const char *fmt, const Args &... args) {
        pInstance->spLogger_->trace(fmt, args...);
    }

    template < typename... Args >
    static void debug(const char *fmt, const Args &... args) {
        pInstance->spLogger_->debug(fmt, args...);
    }

    template < typename... Args >
    static void info(const char *fmt, const Args &... args) {
        pInstance->spLogger_->info(fmt, args...);
    }

    template < typename... Args >
    static void notice(const char *fmt, const Args &... args) {
        pInstance->spLogger_->notice(fmt, args...);
    }

    template < typename... Args >
    static void warn(const char *fmt, const Args &... args) {
        pInstance->spLogger_->warn(fmt, args...);
    }

    template < typename... Args >
    static void error(const char *fmt, const Args &... args) {
        pInstance->spLogger_->error(fmt, args...);
    }

    template < typename... Args >
    static void critical(const char *fmt, const Args &... args) {
        pInstance->spLogger_->critical(fmt, args...);
    }

    template < typename... Args >
    static void alert(const char *fmt, const Args &... args) {
        pInstance->spLogger_->alert(fmt, args...);
    }

    template < typename... Args >
    static void emerg(const char *fmt, const Args &... args) {
        pInstance->spLogger_->emerg(fmt, args...);
    }

    static void setLevel(LogLevel level) { pInstance->spLogger_->set_level(static_cast< spdlog::level::level_enum >(level)); }

private:
    static Logger *pInstance;
    std::shared_ptr< spdlog::logger > spLogger_;

#ifdef TEMP_PLATFORM_WINDOWS
    // デバッグコンソール出力用ストリームバッファ
    class debug_stream_buf : public std::streambuf {
    public:
        virtual int_type overflow(int_type c = EOF) {
            if (c != EOF) {
                char buf[] = { static_cast< char >(c), '\0' };
                OutputDebugStringA(buf);
                printf(buf);
            }
            return c;
        }
    };

    static debug_stream_buf dsb;
    static std::streambuf *default_rdbuf;
#endif
};

template < typename LoggerCreatorType >
Logger< LoggerCreatorType > *Logger< LoggerCreatorType >::pInstance = nullptr;
#ifdef TEMP_PLATFORM_WINDOWS
template < typename LoggerCreatorType >
typename Logger< LoggerCreatorType >::debug_stream_buf Logger< LoggerCreatorType >::dsb;
template < typename LoggerCreatorType >
std::streambuf *Logger< LoggerCreatorType >::default_rdbuf = nullptr;
#endif

struct ConsoleLoggerCreator {
    static std::shared_ptr< spdlog::logger > create() {
        auto ostream_sink = std::make_shared< spdlog::sinks::ostream_sink_mt >(std::cout);
        return std::make_shared< spdlog::logger >("TempuraConsole", ostream_sink);
    }
};

using ConsoleLogger = Logger< ConsoleLoggerCreator >;
}
}

#endif // GUARD_325c251321394362a453f269833195ae
