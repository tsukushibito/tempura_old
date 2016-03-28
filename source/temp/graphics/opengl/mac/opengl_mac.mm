#include "temp/graphics/opengl/mac/opengl_mac.h"

#import <Cocoa/Cocoa.h>

namespace temp {
namespace graphics {
namespace opengl {
namespace mac {

OpenglContexts createContexts(NsWindow window, Size worker_thread_count) {
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

    // コンテキストの作成
    NSOpenGLContext *context_for_render =
        [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

    NSWindow *ns_window = (__bridge NSWindow *)window;
    NSView *ns_view = [ns_window contentView];
    [context_for_render setView:ns_view];

    // カレントコンテキストに設定
    [context_for_render makeCurrentContext];

#ifdef TEMP_USE_GLEW
    // GLEWの初期化
    glewExperimental = TRUE; // OSXの場合はこの設定をしないと正しく初期化できない
    // INVALID_ENUM のエラーがとなるが拡張機能の設定は正しくできているっぽいです。
    glewInit();
    glGetError();
#endif

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

    // 戻り値用に保存
    OpenglContexts contexts;
    contexts.context_for_render_thread = context_for_render;

    // 他スレッド用のコンテキストを作成
    // アプリ実行スレッド用
    NSOpenGLContext *context_for_app =
    [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:context_for_render];
    contexts.context_for_application_thread = context_for_app;
    
    // メインスレッド用
    NSOpenGLContext *context_for_main =
    [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:context_for_render];
    contexts.context_for_main_thread = context_for_main;
    
    // ロードスレッド用
    NSOpenGLContext *context_for_load =
        [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:context_for_render];
    contexts.context_for_load_thread = context_for_load;
    
    // ワーカースレッド用
    for (Size i = 0; i < worker_thread_count; ++i) {
        NSOpenGLContext *context =
            [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:context_for_render];
        contexts.contexts_for_worker_thread.push_back(context);
    }
    
    [NSOpenGLContext clearCurrentContext];
    
    return contexts;
}
    
void deleteContexts(const OpenglContexts &contexts) {
}

void makeCurrent(NsWindow window, NsOpenglContext context) {
    if (context == nullptr) {
        [NSOpenGLContext clearCurrentContext];
    }
    else {
        NSOpenGLContext *ns_context = (__bridge NSOpenGLContext*)context;
        [ns_context makeCurrentContext];
    }
}
    
void swapBuffers(NsWindow window, NsOpenglContext context) {
    NSOpenGLContext *ns_context = (__bridge NSOpenGLContext*)context;
    [ns_context flushBuffer];
}

}
}
}
}
