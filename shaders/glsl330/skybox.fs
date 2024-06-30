#version 330

in vec3 fragPosition;
out vec4 outColor;

uniform samplerCube environmentMap;
uniform bool doGamma;

void main()
{
    vec3 color = texture(environmentMap, fragPosition).rgb;

    if (doGamma) // Apply gamma correction
    {
        color = color/(color + vec3(1.0));
        color = pow(color, vec3(1.0/2.2));
    }

    outColor = vec4(color, 1.0);
}