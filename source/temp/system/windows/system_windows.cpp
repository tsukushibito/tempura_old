#include "temp/system/windows/system_windows.h"
#include "temp/container.h"
#include "temp/system/window.h"

#include <iostream>
#include <mutex>

namespace temp {
namespace system {
namespace windows {

namespace {
    std::mutex g_handle_table_mutex;
    Vector<HWND> g_handle_table;
}

WindowHandle pushHWNDToTable(HWND hwnd) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    for (Int32 i = 0; i < g_handle_table.size(); ++i) {
        if (g_handle_table[i] == hwnd) {
            std::cout << "HWND[0x" << std::hex << hwnd << "] already exists in table!" << std::endl;
            return WindowHandle(i);
        }
        else if (g_handle_table[i] == nullptr) {
            return WindowHandle(i);
        }
    }

    g_handle_table.push_back(hwnd);

    return WindowHandle(static_cast<Int32>(g_handle_table.size()) - 1);
}

void removeNsWindowFromTable(HWND hwnd) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    for (Int32 i = 0; i < g_handle_table.size(); ++i) {
        if (g_handle_table[i] == hwnd) {
            g_handle_table[i] = nullptr;
            return;
        }
    }
    std::cout << "HWND[0x" << std::hex << hwnd << "] is not found in table!" << std::endl;
}

HWND windowHandleToHWND(const WindowHandle& handle){
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