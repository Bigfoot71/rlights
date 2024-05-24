#version 100

attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;
attribute vec4 vertexTangent;
attribute vec3 vertexNormal;
attribute vec4 vertexColor;

uniform lowp int useNormalMap;
uniform mat4 matNormal;
uniform mat4 matModel;
uniform mat4 mvp;

varying vec3 fragPosition;
varying vec2 fragTexCoord;
varying vec3 fragNormal;
varying vec4 fragColor;
varying mat3 TBN;

void main()
{
    fragPosition = vec3(matModel*vec4(vertexPosition, 1.0));
    fragNormal = (matNormal*vec4(vertexNormal, 0.0)).xyz;

    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    if (useNormalMap != 0)
    {
        vec3 T = normalize(vec3(matModel*vec4(vertexTangent.xyz, 0.0)));
        vec3 B = cross(fragNormal, T)*vertexTangent.w;
        TBN = mat3(T, B, fragNormal);
    }

    gl_Position = mvp*vec4(vertexPosition, 1.0);
};