#pragma once
#define FMT_HEADER_ONLY
#include "temp/core//define.h"
#if defined(TEMP_PLATFORM_WINDOWS)
#pragma warning(disable : 4127)
#endif
#include <fmt/format.h>

namespace temp {
namespace fmt = ::fmt;
}