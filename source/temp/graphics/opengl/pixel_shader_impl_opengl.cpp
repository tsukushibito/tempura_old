/**
 * @file pixel_shader_impl_opengl.cpp
 * @brief OpenGL pixel shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/pixel_shader.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/pixel_shader_impl_opengl.h"

namespace temp {
namespace graphics {
namespace {
	GLuint createOpenglPixelShaderFromSource(const String &source) {
		using namespace opengl;
		GLuint pixel_shader = glCallWithErrorCheck(glCreateShader, GL_FRAGMENT_SHADER);
		const GLchar *src_string = source.c_str();
		const GLint length = static_cast<GLint>(source.size());
		glCallWithErrorCheck(glShaderSource, pixel_shader, (GLsizei)1, &src_string, &length);
		glCallWithErrorCheck(glCompileShader, pixel_shader);

		GLsizei size, len;
		glGetShaderiv(pixel_shader, GL_INFO_LOG_LENGTH, &size);
		if (size > 1) {
			Vector<char> log(size);
			glGetShaderInfoLog(pixel_shader, size, &len, &log[0]);
			system::ConsoleLogger::trace("[OpenGL shader info log] \n{0}", &log[0]);
		}

		return pixel_shader;
	}

	GLuint createOpenglPixelShaderFromBinary(const String &source) {
		return 0;
	}
}
    

PixelShader::Impl::Impl(NativeHandle device, PixelShader &pixel_shader, const String &source, Bool is_binary)
    : pixel_shader_(pixel_shader) {
	if (is_binary) {
		pixel_shader_.native_handle_.value = createOpenglPixelShaderFromBinary(source);
	}
	else {
		pixel_shader_.native_handle_.value = createOpenglPixelShaderFromSource(source);
	}
    temp::system::ConsoleLogger::trace("OpenGL Fragment Shader has created! id = {0}", pixel_shader_.getNativeHandle().value);
        
    (void)device;
}

PixelShader::Impl::~Impl() {
    using namespace opengl;
    GLuint pixel_shader = pixel_shader_.getNativeHandle().value;
    glCallWithErrorCheck(glDeleteShader, pixel_shader);
    temp::system::ConsoleLogger::trace("OpenGL Fragmentx Shader has deleted! id = {0}", pixel_shader);
}

    
} // namespace graphics
} // namespace temp
#endif
