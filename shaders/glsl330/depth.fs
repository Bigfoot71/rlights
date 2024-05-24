#version 330

out vec4 outDepth;

void main()
{
    outDepth = vec4(gl_FragCoord.z);
};