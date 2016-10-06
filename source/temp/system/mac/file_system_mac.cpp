/**
 * @file file_system.cpp
 * @brief mac file
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-22
 */

#include "temp/define.h"
#include "temp/system/file_system.h"
namespace {
	char dummy;	// VisualStudio ‚Ì warning LNK4221 ‰ñ”ð‚Ì‚½‚ß
}
#ifdef TEMP_PLATFORM_MAC
#include <stdlib.h>
#include <unistd.h>

namespace temp {
namespace system {
namespace mac {

void setCurrentDirectoryImpl(const Path &path) {
    if (chdir(path.getAbsolute().c_str())) {
    } else {
    }
}

Path getCurrentDirectoryImpl() {
    const Size kBufferSize = PATH_MAX + 1;
    char currentDir[kBufferSize] = {};
    String currentDirStr;
    if (getcwd(currentDir, kBufferSize)) {
        currentDirStr = currentDir;
    } else {
    }

    return Path(currentDirStr);
}
} // namespace mac

void Path::convertToAbsolutePath(String &string) {
    const Size kBufferSize = PATH_MAX + 1;
    char abs_path[kBufferSize] = {};
    if (realpath(string.c_str(), abs_path)) {
        string = abs_path;
    } else {
        auto n = errno;
        printf("%s \n", strerror(n));
    }
}

void setCurrentDirectory(const Path &path) { mac::setCurrentDirectoryImpl(path); }

Path getCurrentDirectory() { return mac::getCurrentDirectoryImpl(); }

} // namespace system
} // namespace temp

#endif
