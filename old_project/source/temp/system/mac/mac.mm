/**
* @file mac.mm
* @brief 
* @author tsukushibito
* @version 0.0.1
* @date 2017-03-14
*/

#include <iostream>
#include <mutex>
#include "temp/container.h"
#include "temp/system/window.h"
#include "temp/system/mac/mac.h"

namespace temp {
namespace system {
namespace mac {

namespace {
    std::mutex g_handle_table_mutex;
    Vector<NSWindow*> g_handle_table;
}

WindowHandle pushNsWindowToTable(NSWindow* ns_window) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    for (Int32 i = 0; i < g_handle_table.size(); ++i) {
        if (g_handle_table[i] == ns_window) {
            std::cout << "NSWindow[0x" << std::hex << ns_window << "] already exists in table!" << std::endl;
            return WindowHandle(i);
        }
        else if (g_handle_table[i] == nullptr) {
            return WindowHandle(i);
        }
    }

    g_handle_table.push_back(ns_window);

    return WindowHandle(g_handle_table.size() - 1);
}

void removeNsWindowFromTable(NSWindow* ns_window) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    for (Int32 i = 0; i < g_handle_table.size(); ++i) {
        if (g_handle_table[i] == ns_window) {
            g_handle_table[i] = nullptr;
            return;
        }
    }
    std::cout << "NSWindow[0x" << std::hex << ns_window << "] is not found in table!" << std::endl;
}

NSWindow* windowHandleToNSWindow(const WindowHandle& handle) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    if(handle.value() >= g_handle_table.size()) {
        std::cout << "WindowHandle[" << handle.value() << "] is invalid." << std::endl;
        return nullptr;
    }
    return g_handle_table[handle.value()];
}

}
}
}
