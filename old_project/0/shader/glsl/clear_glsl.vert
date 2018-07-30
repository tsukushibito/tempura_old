// GLSL test vertex shader code
#version 410

layout (std140) uniform ClearParameters
{
    vec4 uClearColor;
    float uClearDepth;
};

in vec2 vPosition;
out vec4 clearColor;

void main(void)
{
    clearColor = uClearColor;
    gl_Position = vec4(vPosition.x, vPosition.y, uClearDepth, 1.0f);
    // clearColor = vec4(vPosition.x, vPosition.y, uClearDepth, 1.0f);

    // float x = -1.0f + 2.0f * (gl_VertexID % 2);
    // float y = -1.0f + 2.0f * (gl_VertexID / 2);
    // gl_Position = vec4(x, y, 0.0f, 1.0f);
}
