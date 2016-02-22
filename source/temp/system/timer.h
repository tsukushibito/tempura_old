/**
 * @file Timer.h
 * @brief タイマークラス
 * @author tsukushibito
 * @version 0.0.1
 * @date 2014-10-30
 */
#pragma once
#ifndef GUARD_bb53053fe21d4c4fbec1c796aca1ae18
#define GUARD_bb53053fe21d4c4fbec1c796aca1ae18

#include <chrono>
#include "temp/type.h"

namespace temp {
namespace system {
class Timer {
public:
    Timer();
    void reset();
    Int64 nanoseconds() const;
    Int64 microseconds() const;
    Int64 milliseconds() const;
    Int64 seconds() const;
    Int64 minutes() const;
    Int64 hours() const;

private:
    std::chrono::high_resolution_clock::time_point time_point_;
};
}
}
#endif // GUARD_bb53053fe21d4c4fbec1c796aca1ae18
