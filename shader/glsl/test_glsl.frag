// GLSL test fragment shader code
#version 410

uniform Material
{
    vec4 materialColor;
};

in vec3 normal;

out vec4 color;

void main(void)
{
    color = materialColor;
}
