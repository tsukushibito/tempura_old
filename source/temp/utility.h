/**
 * @file utility.h
 * @brief utility
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-05-25
 */
#pragma once
#ifndef GUARD_ab3eabae086c462da5846bb0dd37aff7
#define GUARD_ab3eabae086c462da5846bb0dd37aff7

#include <functional>

#include "temp/container.h"

namespace temp {

class Event {
public:
    Event() {}

    void addFunction(const std::function<void()> &function) {
        function_queue_.push_back(function);
    }

    void clear() { function_queue_.clear(); }

    void execute() {
        while (function_queue_.size() > 0) {
            auto &&func = function_queue_.front();
            func();
            function_queue_.pop_front();
        }
    }

private:
    Deque<std::function<void()>> function_queue_;
};

}  // namespace temp

#endif  // GUARD_ab3eabae086c462da5846bb0dd37aff7
