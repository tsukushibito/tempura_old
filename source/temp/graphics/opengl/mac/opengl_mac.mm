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

OpenGLContextHandle createContext(void* ns_window) {
    NSWindow* window = (__bridge NSWindow*)ns_window;
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

    return context;
}

void deleteContext(OpenGLContextHandle context) {
    NSOpenGLContext* ns_context = (__bridge NSOpenGLContext*)context;
    ns_context = nil;
}

void makeCurrent(OpenGLContextHandle context) {
    NSOpenGLContext *ns_context = (__bridge NSOpenGLContext*)context;

    if (ns_context == nullptr) {
        [NSOpenGLContext clearCurrentContext];
    } else {
        [ns_context makeCurrentContext];
    }
}

void swapBuffers(OpenGLContextHandle context) {
    NSOpenGLContext *ns_context = (__bridge NSOpenGLContext*)context;

    [ns_context flushBuffer];
}

    
}
}
}
}
