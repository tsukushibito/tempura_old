#pragma once
#include "temp/core/core.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/system/mac/mac_application.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/system/windows/windows_application.h"
#endif