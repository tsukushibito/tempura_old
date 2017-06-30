#include "temp/graphics/opengl/opengl_vertex_buffer.h"

#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/opengl_define.h"
namespace temp {
namespace graphics {
namespace opengl {

const ByteData OpenGLVertexBuffer::data() const {
    auto future = device_thread_->pushJob([this]() {
        glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, nativeHandle());
        GLint size;
        glCallWithErrorCheck(glGetBufferParameteriv, GL_ARRAY_BUFFER,
                             GL_BUFFER_SIZE, &size);
        ByteData byte_data(size);
        auto     mapped
            = glCallWithErrorCheck(glMapBuffer, GL_ARRAY_BUFFER, GL_READ_ONLY);
        memcpy(&byte_data[0], mapped, size);
        glCallWithErrorCheck(glUnmapBuffer, GL_ARRAY_BUFFER);
        glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, 0);

        return byte_data;
    });

    return future.get();
}
}
}
}
#endif
