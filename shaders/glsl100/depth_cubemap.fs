#version 100

precision mediump float;

varying vec3 fragPosition;

uniform vec3 lightPos;
uniform float farPlane;

void main()
{
    float lightDistance = length(fragPosition - lightPos);
    lightDistance = lightDistance/farPlane;
    gl_FragDepth = lightDistance;
}
