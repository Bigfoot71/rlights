#version 330

in vec2 fragTexCoord;

uniform sampler2D texture0;
uniform float near;
uniform float far;

out vec4 outColor;

void main()
{
    float depth = texture(texture0, vec2(fragTexCoord.x, 1.0 - fragTexCoord.y)).r;
    depth = (2.0*near*far)/(far + near - (depth*2.0 - 1.0)*(far - near));
    outColor = vec4(vec3(depth/far), 1.0);
};