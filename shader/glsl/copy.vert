// GLSL copy vertex shader code
#version 410

in vec2 Position;
in vec2 TexCoord0;

out vec2 texCoord;

out gl_PerVertex {
    vec4 gl_Position;
};

void main(void)
{
    gl_Position = vec4(Position.x, Position.y, 0.0f, 1.0f);
    texCoord = TexCoord0;
}
