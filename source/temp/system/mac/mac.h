/**
 * @file mac.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-10
 */
#pragma once
#ifndef GUARD_ca4850759ce74f36a48df439e1142612
#define GUARD_ca4850759ce74f36a48df439e1142612

#include "temp/define.h"
#include "temp/type.h"
#ifdef TEMP_PLATFORM_MAC
#import <Cocoa/Cocoa.h>


namespace temp {
namespace system {

class Window;
using WindowHandle = temp::Handle<Window>;

namespace mac {

WindowHandle pushNsWindowToTable(NSWindow* ns_window);

void removeNsWindowFromTable(NSWindow* ns_window);

NSWindow* windowHandleToNSWindow(const WindowHandle& handle);
}
}
}

#endif

#endif  // GUARD_ca4850759ce74f36a48df439e1142612
