// GLSL test vertex shader code
#version 410

uniform TransformMatrix
{
    mat4 worldMatrix;
    mat4 viewMatrix;
    mat4 projMatrix;
    mat4 worldViewMatrix;
    mat3 normalMatrix;
    mat4 worldViewProjMatrix;
};

in vec3 vertexPosition;
in vec3 vertexNormal;

out vec3 normal;

void main(void)
{
    normal = normalize(normalMatrix * vertexNormal);
    gl_Position = worldViewProjMatrix * vec4(vertexPosition, 1.0);
}
