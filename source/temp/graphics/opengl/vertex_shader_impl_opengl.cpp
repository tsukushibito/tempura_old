/**
 * @file vertex_shader_impl_opengl.cpp
 * @brief OpenGL vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-08
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/vertex_shader.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/vertex_shader_impl_opengl.h"

namespace temp {
namespace graphics {

namespace {
	GLuint createOpenglVertexShaderFromSource(const String &source) {
		using namespace opengl;
		GLuint vertex_shader = glCallWithErrorCheck(glCreateShader, GL_VERTEX_SHADER);
		const GLchar *src_string = source.c_str();
		const GLint length = static_cast<GLint>(source.size());
		glCallWithErrorCheck(glShaderSource, vertex_shader, (GLsizei)1, &src_string, &length);
		glCallWithErrorCheck(glCompileShader, vertex_shader);

		GLsizei size, len;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &size);
		if (size > 1) {
			Vector<char> log(size);
			glGetShaderInfoLog(vertex_shader, size, &len, &log[0]);
			system::ConsoleLogger::trace("[OpenGL shader info log] \n{0}", &log[0]);
		}

		return vertex_shader;
	}

	GLuint createOpenglVertexShaderFromBinary(const String &binary) {
		(void*)&binary;
		return 0;
	}
}

VertexShader::Impl::Impl(VertexShader &vertex_shader, const String &source, bool is_binary) 
	: vertex_shader_(vertex_shader) {
	if (is_binary) {
		vertex_shader_.native_handle_.value_ = createOpenglVertexShaderFromBinary(source);
	}
	else {
		vertex_shader_.native_handle_.value_ = createOpenglVertexShaderFromSource(source);
	}

	temp::system::ConsoleLogger::trace("OpenGL Vertex Shader has created! id = {0}", vertex_shader_.getNativeHandle().value_);
}

VertexShader::Impl::~Impl() {
	using namespace opengl;
	GLuint vertex_shader = vertex_shader_.getNativeHandle().value_;
	glCallWithErrorCheck(glDeleteShader, vertex_shader);
	temp::system::ConsoleLogger::trace("OpenGL Vertex Shader has deleted! id = {0}", vertex_shader);
}

    
} // namespace graphics
} // namespace temp
#endif