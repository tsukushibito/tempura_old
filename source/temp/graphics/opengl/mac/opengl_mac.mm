#include "temp/graphics/opengl/mac/opengl_mac.h"

#import <Cocoa/Cocoa.h>

namespace temp {
namespace graphics {
namespace opengl {
namespace mac {

OpenglContexts createContext(NsWindow window) {
    // ピクセルフォーマット指定
    NSOpenGLPixelFormatAttribute att[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
        NSOpenGLPFADoubleBuffer, YES,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFANoRecovery, YES,
        NSOpenGLPFAAccelerated, YES,
        0, 0};

    // 初期化
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:att];
    if (pixelFormat == nil) return; // TODO: バージョンを下げた設定で作成し直す

    // 
    NSOpenGLContext *context_for_render =
        [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    NSOpenGLContext *context_for_load =
        [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:context_for_render];

    NSWindow *ns_window = (__bridge NSWindow *)window;
    NSView *ns_view = [ns_window contentView];
    [context_for_render setView:ns_view];

    // カレントコンテキストに設定
    [context_for_render makeCurrentContext];

    // GLEWの初期化
    glewExperimental = TRUE; // OSXの場合はこの設定をしないと正しく初期化できない
    // INVALID_ENUM のエラーがとなるが拡張機能の設定は正しくできているっぽいです。
    glewInit();
    glGetError();

    // バージョン情報ログ
    const GLubyte *version;
    version = glGetString(GL_VERSION);
    std::string msg("OpenGL version : ");
    msg += (const char *)version;
    std::cout << msg << std::endl;

    const GLubyte *glslVersion;
    glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    msg = std::string("GLSL version : ") + (const char *)glslVersion;
    std::cout << msg.c_str() << std::endl;

    OpenglContexts contexts;
    
    contexts.context_for_render = context_for_render;
    contexts.context_for_load = context_for_load;
    
    return contexts;
}

void makeCurrent(NsOpenglContext context) {
    if (context == nullptr) {
        [NSOpenGLContext clearCurrentContext];
    }
    else {
        NSOpenGLContext *ns_context = (__bridge NSOpenGLContext*)context;
        [ns_context makeCurrentContext];
    }
}

}
}
}
}
