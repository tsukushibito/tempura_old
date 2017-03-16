#include "temp/container.h"
#include "temp/graphics/opengl/opengl_define.h"
#include "temp/graphics/opengl/mac/opengl_mac.h"
#include "temp/system/mac/mac.h"
#include <iostream>
#include <string>
#include <mutex>
#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>


namespace temp {
namespace graphics {
namespace opengl {
namespace mac {

namespace {
    temp::Vector<NSOpenGLContext*> g_handle_table;
    std::mutex g_handle_table_mutex;

    DeviceHandle pushNSOpenGLContextToTable(NSOpenGLContext* context) {
        std::lock_guard<std::mutex> lock(g_handle_table_mutex);
        NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;
        for (Int32 i = 0; i < g_handle_table.size(); ++i) {
            if (g_handle_table[i] == ns_context) {
                std::cout << "NSOpenGLContext[0x" << std::hex << ns_context << "] already exists in table!" << std::endl;
                return DeviceHandle(i);
            }
            else if (g_handle_table[i] == nullptr) {
                return DeviceHandle(i);
            }
        }

        g_handle_table.push_back(ns_context);
        return DeviceHandle(g_handle_table.size() - 1);
    }

    void removeNSOpenGLContextFromTable(NSOpenGLContext* context) {
        std::lock_guard<std::mutex> lock(g_handle_table_mutex);
        NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;
        for (Int32 i = 0; i < g_handle_table.size(); ++i) {
            if (g_handle_table[i] == ns_context) {
                g_handle_table[i] = nullptr;
                return;
            }
        }
        std::cout << "NSOpenGLContext[0x" << std::hex << ns_context << "] is not found in table!" << std::endl;
    }

    NSOpenGLContext* deviceHandleToNSOpenGLContext(const DeviceHandle& handle) {
        std::lock_guard<std::mutex> lock(g_handle_table_mutex);
        return nullptr;
    }
}
    
DeviceHandle createContext(const temp::system::WindowHandle& window_handle) {
    NSWindow* window = temp::system::mac::windowHandleToNSWindow(window_handle);
    // ピクセルフォーマット指定
    NSOpenGLPixelFormatAttribute att[] = {NSOpenGLPFAOpenGLProfile,
                                          NSOpenGLProfileVersion4_1Core,
                                          NSOpenGLPFADoubleBuffer,
                                          YES,
                                          NSOpenGLPFAColorSize,
                                          24,
                                          NSOpenGLPFAAlphaSize,
                                          8,
                                          NSOpenGLPFADepthSize,
                                          24,
                                          NSOpenGLPFANoRecovery,
                                          YES,
                                          NSOpenGLPFAAccelerated,
                                          YES,
                                          0,
                                          0};

    // 初期化
    NSOpenGLPixelFormat* pixelFormat =
        [[NSOpenGLPixelFormat alloc] initWithAttributes:att];
    if (pixelFormat == nil) {
        return DeviceHandle();  // TODO: バージョンを下げた設定で作成し直す
    }

    // コンテキストの作成
    NSOpenGLContext* context =
        [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

    NSView* ns_view     = [window contentView];
    [context setView:ns_view];

    // カレントコンテキストに設定
    [context makeCurrentContext];

    // バージョン情報ログ
    const GLubyte* version;
    version = glGetString(GL_VERSION);
    std::string msg("OpenGL version : ");
    msg += (const char*)version;
    std::cout << msg << std::endl;

    const GLubyte* glslVersion;
    glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    msg         = std::string("GLSL version : ") + (const char*)glslVersion;
    std::cout << msg.c_str() << std::endl;

    [NSOpenGLContext clearCurrentContext];

    return pushNSOpenGLContextToTable(context);
}

void deleteContext(void* context) {
    removeNSOpenGLContextFromTable((__bridge NSOpenGLContext*)context);
}

void makeCurrent(void* context) {
    NSOpenGLContext *ns_context = (__bridge NSOpenGLContext*)context;

    if (ns_context == nullptr) {
        [NSOpenGLContext clearCurrentContext];
    } else {
        [ns_context makeCurrentContext];
    }
}

void swapBuffers(void* context) {
    NSOpenGLContext *ns_context = (__bridge NSOpenGLContext*)context;

    [ns_context flushBuffer];
}
    
void* deviceHandleToNsOpenGlContext(const DeviceHandle& handle) {
    return deviceHandleToNSOpenGLContext(handle);
}

    
}
}
}
}
