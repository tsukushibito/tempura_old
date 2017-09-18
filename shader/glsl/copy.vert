// GLSL copy vertex shader code
#version 410

in vec2 Position;
in vec2 TexCoord0;

out vec2 texCoord;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main(void)
{
    // int x = (gl_VertexID & 1) * -2 + 1;
    // int y = (gl_VertexID & 2) * -1 + 1;
    // gl_Position = vec4(x, y, 0.0f, 1.0f);
    gl_Position = vec4(Position.x, Position.y, 0.0f, 1.0f);
    texCoord = TexCoord0;
}
