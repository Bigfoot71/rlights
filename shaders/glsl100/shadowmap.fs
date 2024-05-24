#version 100

precision mediump float;

varying vec2 fragTexCoord;

uniform sampler2D texture0;
uniform float near;
uniform float far;

void main()
{
    float depth = texture2D(texture0, vec2(fragTexCoord.x, 1.0 - fragTexCoord.y)).r;
    depth = (2.0*near*far)/(far + near - (depth*2.0 - 1.0)*(far - near));
    gl_FragColor = vec4(vec3(depth/far), 1.0);
};