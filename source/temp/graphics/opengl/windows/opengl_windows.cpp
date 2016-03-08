#include "temp/graphics/opengl/windows/opengl_windows.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <iostream>
#include <sstream>

namespace {

// �_�~�[�E�B���h�E�쐬
HWND createDummyWindow() {
    const size_t kMaxStrSize = 100;
    HINSTANCE instance_handle = GetModuleHandle(NULL);
    CHAR window_class_name[kMaxStrSize] = "Dummy";
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = DefWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = instance_handle;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = window_class_name;
    wcex.hIconSm = NULL;

    RegisterClassEx(&wcex);

    return CreateWindow(window_class_name, "", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL,
                        instance_handle, NULL);
}

// �_�~�[�R���e�L�X�g�쐬
HGLRC createDummyOpenglContext(HDC hdc) {
    // ���ݑΉ����Ă���t�H�[�}�b�g�̐����Q�Ƃ���
    // int format_count= DescribePixelFormat( hTempDC, 0, 0, NULL );

    PIXELFORMATDESCRIPTOR pfd;
    // �񋓂���
    // for (int i = 0; i < format_count; ++i) {
    //     DescribePixelFormat(hTempDC, i + 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    //     break;
    // }
    DescribePixelFormat(hdc, 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    // �s�N�Z���t�H�[�}�b�g�̑I��
    int pfmt = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pfmt, &pfd);

    // OpenGL �R���e�L�X�g�̍쐬
    return wglCreateContext(hdc);
}

} // namespace

namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

OpenglContexts createContexts(HWND window_handle, Size worker_thread_count) {
    // glew�������p�̃_�~�[�E�B���h�E�ƃR���e�L�X�g���쐬
    auto dummy_window_handle = createDummyWindow();
    auto dummy_device_context = GetDC(dummy_window_handle);
    auto dummy_opengl_context = createDummyOpenglContext(dummy_device_context);
    glCallWithErrorCheck(wglMakeCurrent, dummy_device_context, dummy_opengl_context);

    // glew�̏�����
    GLenum error = glewInit();

    // �g���@�\�ɂ��R���e�L�X�g�̍쐬
    const FLOAT fAtribList[] = { 0, 0 };

    // �s�N�Z���t�H�[�}�b�g�w��p
    const int pixel_format_attrib_list[] = {
        // WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
        // WGL_CONTEXT_MINOR_VERSION_ARB, 0,
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, //
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE, //
        WGL_DOUBLE_BUFFER_ARB,  GL_TRUE, //
        // WGL_DOUBLE_BUFFER_ARB, GL_FALSE, //
        WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB, //
        WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,         //
        WGL_COLOR_BITS_ARB,     32,                        //
        WGL_DEPTH_BITS_ARB,     24,                        //
        WGL_STENCIL_BITS_ARB,   8,                         //
        0,                      0,                         //
    };

    // �R���e�L�X�g�쐬�p
    int context_attrib_list[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB,
        4, //
        WGL_CONTEXT_MINOR_VERSION_ARB,
        5, //
#if DEBUG
        WGL_CONTEXT_FLAGS_ARB,
        WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
        WGL_CONTEXT_PROFILE_MASK_ARB,
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
        0, // End
    };

    int pixelFormat = 0;
    UINT numFormats = 0;
    HDC hdc = GetDC(window_handle);

    // �s�N�Z���t�H�[�}�b�g�I��
    BOOL isValid = wglChoosePixelFormatARB(hdc, pixel_format_attrib_list, fAtribList, 1, &pixelFormat, &numFormats);

    error = glGetError();
    if (isValid == FALSE) {
        assert(false);
    }

    // �s�N�Z���t�H�[�}�b�g�ݒ�
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    BOOL result = SetPixelFormat(hdc, pixelFormat, &pfd);
    if (result == FALSE) {
        assert(false);
    }

    // �R���e�L�X�g�쐬
    OpenglContexts output;

    // �`��X���b�h�p
    output.context_for_render_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    while (output.context_for_render_thread == NULL) {
        // ��������܂Ńo�[�W������������
        context_attrib_list[3] -= 1;
        if (context_attrib_list[3] < 0) {
            context_attrib_list[3] = 10;
            context_attrib_list[1] -= 1;
            if (context_attrib_list[1] < 0) {
                break;
            }
        }
        output.context_for_render_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    }

    // ���C���X���b�h�p
    output.context_for_main_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    wglShareLists((HGLRC)output.context_for_render_thread, (HGLRC)output.context_for_main_thread);

    // ���[�h�X���b�h�p
    output.context_for_load_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    wglShareLists((HGLRC)output.context_for_render_thread, (HGLRC)output.context_for_load_thread);

	for (Size i = 0; i < worker_thread_count; ++i) {
        auto context = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
		output.contexts_for_worker_thread.push_back(context);
        wglShareLists((HGLRC)output.context_for_render_thread, context);
	}

    // �J�����g�R���e�L�X�g������
    glCallWithErrorCheck(wglMakeCurrent, dummy_device_context, (HGLRC)NULL);

    // �_�~�[�̃R���e�L�X�g�ƃE�B���h�E���폜
    glCallWithErrorCheck(wglDeleteContext, dummy_opengl_context);
    ReleaseDC(dummy_window_handle, dummy_device_context);
    DestroyWindow(dummy_window_handle);

    return output;
}

void deleteContexts(const OpenglContexts &contexts) {
	glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(contexts.context_for_main_thread));
	glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(contexts.context_for_render_thread));
	glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(contexts.context_for_load_thread));
	for (auto &&context : contexts.contexts_for_worker_thread)
	{
		glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(context));
	}
}

void makeCurrent(HWND window_handle, HGLRC context) {
	HDC hdc = GetDC(window_handle);
	wglMakeCurrent(hdc, context);
}

} // namespace windows
} // namespace opengl
} // namespace graphics
} // namespace

#endif // TEMP_PLATFORM_WINDOWS
