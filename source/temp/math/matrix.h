/**
 * @file matrix.h
 * @brief matrix
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-01
 */
#pragma once
#ifndef GUARD_b00e28b25c664a42adda994baba46c75
#define GUARD_b00e28b25c664a42adda994baba46c75

#include "temp/type.h"
#include "temp/temp_assert.h"

namespace temp {
namespace math {
    
class Matrix {
public:
private:
    Float32 m_[4][4];
};
    
} // namespace math
} // namespace temp

#endif // GUARD_b00e28b25c664a42adda994baba46c75
