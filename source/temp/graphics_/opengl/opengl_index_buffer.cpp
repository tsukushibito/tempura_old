#include "temp/graphics_/opengl/opengl_index_buffer.h"

#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_/opengl/opengl_define.h"
#include "temp/graphics_/opengl/opengl_common.h"

namespace temp {
namespace graphics_ {
namespace opengl {

const ByteData OpenGLIndexBuffer::data() const {
    auto future = device_thread_->pushJob([this]() {
        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER,
                             nativeHandle());
        GLint size;
        glCallWithErrorCheck(glGetBufferParameteriv, GL_ELEMENT_ARRAY_BUFFER,
                             GL_BUFFER_SIZE, &size);
        ByteData byte_data(size);
        auto mapped = glCallWithErrorCheck(glMapBuffer, GL_ELEMENT_ARRAY_BUFFER,
                                           GL_READ_ONLY);
        memcpy(&byte_data[0], mapped, size);
        glCallWithErrorCheck(glUnmapBuffer, GL_ELEMENT_ARRAY_BUFFER);
        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);

        return byte_data;
    });

    return future.get();
}
}
}
}
#endif
