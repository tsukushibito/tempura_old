// GLSL copy fragment shader code
#version 410

in vec2 texCoord;

uniform sampler2D AlbedoMap;

out vec4 Color0;

void main(void)
{
    Color0 = texture(AlbedoMap, texCoord);
    // Color0.x = texCoord.x;
    // Color0.y = texCoord.y;
    // Color0 = vec4(0.0, 1.0, 1.0, 1.0);
}
