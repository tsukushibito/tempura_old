/**
 * @file file_system.cpp
 * @brief windows file system
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-22
 */

#include "temp/define.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#include "temp/system/file_system.h"

namespace temp {
namespace system {
namespace windows {

void setCurrentDirectoryImpl(const Path &path) {
    if (SetCurrentDirectoryA(path.absolute().c_str())) {
    } else {
    }
}

Path getCurrentDirectoryImpl() {
    const size_t BUFFER_SIZE = _MAX_PATH + 1;
    char buffer[BUFFER_SIZE];
    GetCurrentDirectoryA(BUFFER_SIZE, buffer);
    String currentDirStr = buffer;
    return Path(currentDirStr);
}

} // namespace Windows

void Path::convertToAbsolutePath(String &string) {
    const Size BUFFER_SIZE = _MAX_PATH + 1;
    char absPath[BUFFER_SIZE] = {};
    if (_fullpath(absPath, string.c_str(), BUFFER_SIZE)) {
        string = absPath;
    } else {
    }
}

void setCurrentDirectory(const Path &path) { windows::setCurrentDirectoryImpl(path); }

Path getCurrentDirectory() { return windows::getCurrentDirectoryImpl(); }

} // namespace system
} // namespace temp

#endif
