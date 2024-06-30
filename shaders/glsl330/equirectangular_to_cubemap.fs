#version 330

int vec3 fragPosition;
out vec4 outColor;

uniform sampler2D equirectangularMap;

vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= vec2(0.1591, -0.3183); // negative Y, to flip axis
    uv += 0.5;
    return uv;
}

void main()
{
    vec2 uv = SampleSphericalMap(normalize(fragPosition));
    vec3 color = texture(equirectangularMap, uv).rgb;
    outColor = vec4(color, 1.0);
}