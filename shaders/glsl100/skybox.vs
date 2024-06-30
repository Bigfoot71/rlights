#version 100

attribute vec3 vertexPosition;
varying vec3 fragPosition;

uniform mat4 matProjection;
uniform mat4 matView;

void main()
{
    fragPosition = vertexPosition;
    mat4 rotView = mat4(mat3(matView));
    vec4 clipPos = matProjection*rotView*vec4(vertexPosition, 1.0);
    gl_Position = clipPos;
}