#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>

#include "temp/core/core.h"
#include "temp/graphics/opengl/mac/gl_mac.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace mac {
namespace {
const char* kGlMac = "GlMac";
}

OpenGLContextHandle CreateContext(const void*        window,
                                  OpenGLContextHandle shared_context) {
    NSWindow* ns_window = (__bridge NSWindow*)window;
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
    NSOpenGLPixelFormat* pixel_format =
        [[NSOpenGLPixelFormat alloc] initWithAttributes:att];
    if (pixel_format == nil) {
        return nullptr;  // TODO: バージョンを下げた設定で作成し直す
    }

    NSOpenGLContext* share = (__bridge NSOpenGLContext*)shared_context;

    // コンテキストの作成
    NSOpenGLContext* context =
        [[NSOpenGLContext alloc] initWithFormat:pixel_format shareContext:share];

    NSView* ns_view = [ns_window contentView];
    [context setView:ns_view];
    int swap_interval = 0;
    [context setValues:&swap_interval forParameter:NSOpenGLCPSwapInterval];

    // カレントコンテキストに設定
    [context makeCurrentContext];

    // バージョン情報ログ
    const GLubyte* version;
    version = glGetString(GL_VERSION);
    TEMP_LOG_INFO(kGlMac, fmt::format("OpenGL version : {0}", version));

    const GLubyte* glslVersion;
    TEMP_LOG_INFO(kGlMac, fmt::format("GLSL version : {0}", glslVersion));

    [NSOpenGLContext clearCurrentContext];

    return context;
}

void DeleteContext(OpenGLContextHandle context) {
    NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;
    ns_context                  = nil;
}

void MakeCurrent(const void* window, OpenGLContextHandle context) {
    NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;

    if (ns_context == nullptr) {
        [NSOpenGLContext clearCurrentContext];
    } else {
        [ns_context makeCurrentContext];
    }
}

void SwapBuffers(OpenGLContextHandle context) {
    NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;

    [ns_context flushBuffer];
}

OpenGLContextHandle CreateSharedContext(OpenGLContextHandle shared_context) {
    NSOpenGLContext* context = (__bridge NSOpenGLContext*)shared_context;
    NSView* ns_view          = [context view];
    NSWindow* ns_window      = [ns_view window];
    return CreateContext(ns_window, shared_context);
}
}
}
}
}
