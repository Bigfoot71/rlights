#version 330

#define NUM_LIGHTS %i   ///< Indicate the desired number of lights

#define DIRLIGHT  0
#define OMNILIGHT 1
#define SPOTLIGHT 2

in vec4 fragPosLightSpace[NUM_LIGHTS];
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec4 fragColor;
flat in mat3 TBN;

out vec4 outColor;

struct Light {
    sampler2D shadowMap;      ///< Sampler for the shadow map texture
    vec3 position;            ///< Position of the light in world coordinates
    vec3 direction;           ///< Direction vector of the light (for directional and spotlights)
    vec3 diffuse;             ///< Diffuse color of the light
    vec3 specular;            ///< Specular color of the light
    float innerCutOff;        ///< Inner cutoff angle for spotlights (cosine of the angle)
    float outerCutOff;        ///< Outer cutoff angle for spotlights (cosine of the angle)
    float constant;           ///< Constant attenuation factor
    float linear;             ///< Linear attenuation factor
    float quadratic;          ///< Quadratic attenuation factor
    float shadowMapTxlSz;     ///< Texel size of the shadow map
    float depthBias;          ///< Bias value to avoid self-shadowing artifacts
    lowp int type;            ///< Type of the light (e.g., point, directional, spotlight)
    lowp int shadow;          ///< Indicates if the light casts shadows (1 for true, 0 for false)
    lowp int enabled;         ///< Indicates if the light is active (1 for true, 0 for false)
};

uniform Light lights[NUM_LIGHTS];

uniform lowp int useSpecularMap;
uniform lowp int useNormalMap;

uniform sampler2D texture0;   // diffuse
uniform sampler2D texture1;   // specular
uniform sampler2D texture2;   // normal

uniform vec3 colSpecular;     // sent by rlights
uniform vec4 colDiffuse;      // sent by raylib
uniform vec3 colAmbient;      // sent by rlights

uniform float shininess;
uniform vec3 viewPos;

float ShadowCalc(int i)
{
    vec4 p = fragPosLightSpace[i];

    vec3 projCoords = p.xyz/p.w;
    projCoords = projCoords*0.5 + 0.5;
    projCoords.z -= lights[i].depthBias;

    if (projCoords.z > 1.0 || projCoords.x > 1.0 || projCoords.y > 1.0)
    {
        return 1.0;
    }

    float depth = projCoords.z;
    float shadow = 0.0;

    // NOTE: You can increase iterations to improve PCF quality
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            float pcfDepth = texture(lights[i].shadowMap, projCoords.xy + vec2(x, y)*lights[i].shadowMapTxlSz).r; 
            shadow += step(depth, pcfDepth);
        }
    }

    return shadow/9.0;
}

void main()
{
    // get texture samples
    vec3 diffSample = texture(texture0, fragTexCoord).rgb*colDiffuse.rgb*fragColor.rgb;
    vec3 specSample = (useSpecularMap != 0) ? texture(texture1, fragTexCoord).rgb*colSpecular : colSpecular;

    // ambient
    vec3 ambientColor = colAmbient*diffSample;

    // compute normals
    vec3 normal;
    if (useNormalMap == 0) normal = normalize(fragNormal);
    else normal = normalize(TBN*(texture(texture2, fragTexCoord).rgb*2.0 - 1.0));

    // compute current view dir for this frag
    vec3 viewDir = normalize(viewPos - fragPosition);

    // process lights
    vec3 finalColor = vec3(0.0);
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        if (lights[i].enabled != 0)
        {
            // get lightDir
            vec3 lightDir = (lights[i].type != DIRLIGHT)
                ? normalize(lights[i].position - fragPosition)
                : normalize(-lights[i].direction);

            // diffuse
            float diff = max(dot(normal, lightDir), 0.0);
            vec3 diffuse = lights[i].diffuse*diffSample*diff;

            // specular (Blinn-Phong)
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
            vec3 specular = lights[i].specular*specSample*spec;

            // spotlight
            float intensity = 1.0;
            if (lights[i].type == SPOTLIGHT)
            {
                float theta = dot(lightDir, normalize(-lights[i].direction));
                float epsilon = (lights[i].innerCutOff - lights[i].outerCutOff);
                intensity = smoothstep(0.0, 1.0, (theta - lights[i].outerCutOff) / epsilon);
            }

            // attenuation
            float distance    = length(lights[i].position - fragPosition);
            float attenuation = 1.0/(lights[i].constant + lights[i].linear*distance + lights[i].quadratic*(distance*distance));

            // shadow
            float shadow = (lights[i].shadow != 0) ? ShadowCalc(i) : 1.0;

            // add final light color
            finalColor += (diffuse + specular)*intensity*attenuation*shadow;
        }
    }

    outColor = vec4(ambientColor + finalColor, 1.0);
};