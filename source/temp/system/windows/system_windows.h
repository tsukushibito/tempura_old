/**
 * @file system_windows.h
 * @brief Windows
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-16
 */
#pragma once
#ifndef GUARD_14869c01a77d44feb20adbb8ccb06cdb
#define GUARD_14869c01a77d44feb20adbb8ccb06cdb

#include "temp/define.h"
#ifdef TEMP_PLATFORM_MAC

#include <Windows.h>

namespace temp {
namespace system {

class Window;
using WindowHandle = temp::Handle<Window>;

namespace windows {

WindowHandle pushHWNDToTable(HWND hwnd);

void removeNsWindowFromTable(HWND hwnd);

HWND windowHandleToHWND(const WindowHandle& handle);
}
}
}

#endif

#endif // GUARD_14869c01a77d44feb20adbb8ccb06cdb
