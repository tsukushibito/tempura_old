#pragma once
#include "temp/common/common.h"

namespace temp {
namespace math {
const Float32 kPi = static_cast<Float32>(3.14159265358979323846);
const Float32 k2Pi = 2.0f * kPi;
const Float32 kPi_2 = 0.5f * kPi;
const Float32 kPi_4 = 0.25f * kPi;
inline Float32 degreeToRadian(Float32 deg) { return kPi * (deg / 180.0f); }
inline Float32 radianToDegree(Float32 rad) { return 180.0f * (rad / kPi); }
}  // namespace math
}  // namespace temp