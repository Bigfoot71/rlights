#version 330

in vec3 vertexPosition;
out vec3 fragPosition;

uniform mat4 matModel;
uniform mat4 mvp;

void main()
{
    fragPosition = vec3(matModel*vec4(vertexPosition, 1.0));
    gl_Position = mvp*vec4(vertexPosition, 1.0);
}
