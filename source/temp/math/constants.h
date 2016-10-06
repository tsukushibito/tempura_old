﻿/**
 * @file constants.h
 * @brief constants
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-17
 */
#pragma once
#ifndef GUARD_4a560546b1294abf9fc477f361f28606
#define GUARD_4a560546b1294abf9fc477f361f28606

#include "temp/define.h"
#include "temp/type.h"

namespace temp {
namespace math {

template<typename T>
constexpr T pi();

template<>
Float32 pi() {
    return 3.14159265f;
}

template<>
Float64 pi() {
    return 3.141592653589793;
}

TEMP_DEFINE_ALIAS(pi32, pi<Float32>);
TEMP_DEFINE_ALIAS(pi64, pi<Float64>);

} // namespace math
} // namespace temp

#endif // GUARD_4a560546b1294abf9fc477f361f28606