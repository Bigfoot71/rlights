#version 330

#define NUM_LIGHTS %i   ///< Indicate the desired number of lights

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexTangent;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform mat4 matLights[NUM_LIGHTS];
uniform lowp int useNormalMap;
uniform mat4 matNormal;
uniform mat4 matModel;
uniform mat4 mvp;

out vec4 fragPosLightSpace[NUM_LIGHTS];
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec4 fragColor;
flat out mat3 TBN;

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

    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        fragPosLightSpace[i] = matLights[i]*vec4(fragPosition, 1.0);
    }

    gl_Position = mvp*vec4(vertexPosition, 1.0);
};