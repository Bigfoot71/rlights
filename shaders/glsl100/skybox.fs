#version 100

precision mediump float;

varying vec3 fragPosition;

uniform samplerCube environmentMap;
uniform bool doGamma;

void main()
{
    vec3 color = textureCube(environmentMap, fragPosition).rgb;

    if (doGamma) // Apply gamma correction
    {
        color = color/(color + vec3(1.0));
        color = pow(color, vec3(1.0/2.2));
    }

    gl_FragColor = vec4(color, 1.0);
}