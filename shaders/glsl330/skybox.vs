#version 330

in vec3 vertexPosition;
out vec3 fragPosition;

uniform mat4 matProjection;
uniform mat4 matView;

void main()
{
    fragPosition = vertexPosition;
    mat4 rotView = mat4(mat3(matView));
    vec4 clipPos = matProjection*rotView*vec4(vertexPosition, 1.0);
    gl_Position = clipPos;
}