#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>

#include "temp/common/format.h"
#include "temp/core/logger.h"
#include "temp/graphics/opengl/mac/mac_opengl.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace mac {
namespace {
const char* kOpenGLTag = "OpenGL";
}

OpenGLContextHandle createContext(WindowHandle        window_handle,
                                  OpenGLContextHandle shared_context) {
    NSWindow* window = (__bridge NSWindow*)window_handle;
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
        return nullptr;  // TODO: バージョンを下げた設定で作成し直す
    }

    NSOpenGLContext* share = (__bridge NSOpenGLContext*)shared_context;

    // コンテキストの作成
    NSOpenGLContext* context =
        [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:share];

    NSView* ns_view = [window contentView];
    [context setView:ns_view];
    int swap_interval = 0;
    [context setValues:&swap_interval forParameter:NSOpenGLCPSwapInterval];

    // カレントコンテキストに設定
    [context makeCurrentContext];

    // バージョン情報ログ
    const GLubyte* version;
    version = glGetString(GL_VERSION);
    TEMP_LOG_INFO(kOpenGLTag, fmt::format("OpenGL version : {0}", version));

    const GLubyte* glslVersion;
    TEMP_LOG_INFO(kOpenGLTag, fmt::format("GLSL version : {0}", glslVersion));

    [NSOpenGLContext clearCurrentContext];

    return context;
}

void deleteContext(OpenGLContextHandle context) {
    NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;
    ns_context                  = nil;
}

void makeCurrent(WindowHandle window_handle, OpenGLContextHandle context) {
    NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;

    if (ns_context == nullptr) {
        [NSOpenGLContext clearCurrentContext];
    } else {
        [ns_context makeCurrentContext];
    }
}

void swapBuffers(OpenGLContextHandle context) {
    NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;

    [ns_context flushBuffer];
}

OpenGLContextHandle createSharedContext(OpenGLContextHandle shared_context) {
    NSOpenGLContext* context = (__bridge NSOpenGLContext*)shared_context;
    NSView* ns_view          = [context view];
    NSWindow* ns_window      = [ns_view window];
    return createContext(ns_window, shared_context);
}
}
}
}
}