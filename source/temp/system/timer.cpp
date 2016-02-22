#include "temp/system/timer.h"

namespace temp {
namespace system {

namespace {
using TempClock = std::chrono::high_resolution_clock;
}

Timer::Timer() : time_point_(TempClock::now()) {}

void Timer::reset() { time_point_ = TempClock::now(); }

Int64 Timer::nanoseconds() const {
    using namespace std::chrono;
    auto now = TempClock::now();
    return duration_cast< std::chrono::nanoseconds >(now - time_point_).count();
}

Int64 Timer::microseconds() const {
    using namespace std::chrono;
    auto now = TempClock::now();
    return duration_cast< std::chrono::microseconds >(now - time_point_).count();
}

Int64 Timer::milliseconds() const {
    using namespace std::chrono;
    auto now = TempClock::now();
    return duration_cast< std::chrono::milliseconds >(now - time_point_).count();
}

Int64 Timer::seconds() const {
    using namespace std::chrono;
    auto now = TempClock::now();
    return duration_cast< std::chrono::seconds >(now - time_point_).count();
}

Int64 Timer::minutes() const {
    using namespace std::chrono;
    auto now = TempClock::now();
    return duration_cast< std::chrono::minutes >(now - time_point_).count();
}

Int64 Timer::hours() const {
    using namespace std::chrono;
    auto now = TempClock::now();
    return duration_cast< std::chrono::hours >(now - time_point_).count();
}
}
}
