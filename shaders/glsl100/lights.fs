#version 100

#define NUM_LIGHTS              %i
#define NUM_MATERIAL_MAPS       7
#define NUM_MATERIAL_CUBEMAPS   2

#define DIRLIGHT                0
#define OMNILIGHT               1
#define SPOTLIGHT               2

#define ALBEDO                  0
#define METALNESS               1
#define NORMAL                  2
#define ROUGHNESS               3
#define OCCLUSION               4
#define EMISSION                5
#define HEIGHT                  6

#define CUBEMAP                 0
#define IRRADIANCE              1

#define PI 3.1415926535897932384626433832795028

precision mediump float;

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec4 fragColor;
in mat3 TBN;

struct MaterialMap {
    sampler2D texture;
    mediump vec4 color;
    mediump float value;
    lowp int active;
};

struct MaterialCubemap {
    samplerCube texture;
    mediump vec4 color;
    mediump float value;
    lowp int active;
};

struct Light {
    samplerCube shadowCubemap;    ///< Sampler for the shadow map texture
    sampler2D shadowMap;          ///< Sampler for the shadow map texture
    vec3 position;                ///< Position of the light in world coordinates
    vec3 direction;               ///< Direction vector of the light (for directional and spotlights)
    vec3 color;                   ///< Diffuse color of the light
    float energy;                 ///< Energy factor of the diffuse light color
    float specular;               ///< Specular amount of the light
    float size;                   ///< Light size (spotlight, omnilight only)
    float innerCutOff;            ///< Inner cutoff angle for spotlights (cosine of the angle)
    float outerCutOff;            ///< Outer cutoff angle for spotlights (cosine of the angle)
    float constant;               ///< Constant attenuation factor
    float linear;                 ///< Linear attenuation factor
    float quadratic;              ///< Quadratic attenuation factor
    float shadowMapTxlSz;         ///< Texel size of the shadow map
    float depthBias;              ///< Bias value to avoid self-shadowing artifacts
    lowp int type;                ///< Type of the light (e.g., point, directional, spotlight)
    lowp int shadow;              ///< Indicates if the light casts shadows (1 for true, 0 for false)
    lowp int enabled;             ///< Indicates if the light is active (1 for true, 0 for false)
};

uniform MaterialCubemap cubemaps[NUM_MATERIAL_CUBEMAPS];
uniform MaterialMap maps[NUM_MATERIAL_MAPS];
uniform mat4 matLights[NUM_LIGHTS];
uniform Light lights[NUM_LIGHTS];

uniform lowp int parallaxMinLayers;
uniform lowp int parallaxMaxLayers;

uniform float farPlane;     ///< Used to scale depth values ​​when reading the depth cubemap (point shadows)

uniform vec3 colAmbient;
uniform vec3 viewPos;

float DistributionGGX(float cosTheta, float alpha)
{
    float a = cosTheta*alpha;
    float k = alpha/(1.0 - cosTheta*cosTheta + a*a);
    return k*k*(1.0/PI);
}

// From Earl Hammon, Jr. PBR Diffuse Lighting for GGX+Smith Microsurfaces
// SEE: https://www.gdcvault.com/play/1024478/PBR-Diffuse-Lighting-for-GGX
float GeometrySmith(float NdotL, float NdotV, float alpha)
{
    return 0.5/mix(2.0*NdotL*NdotV, NdotL + NdotV, alpha);
}

float SchlickFresnel(float u)
{
    float m = 1.0 - u;
    float m2 = m*m;
    return m2*m2*m; // pow(m,5)
}

vec3 ComputeF0(float metallic, float specular, vec3 albedo)
{
    float dielectric = 0.16*specular*specular;
    // use albedo*metallic as colored specular reflectance at 0 angle for metallic materials
    // SEE: https://google.github.io/filament/Filament.md.html
    return mix(vec3(dielectric), albedo, vec3(metallic));
}

vec2 Parallax(vec2 uv, vec3 V)
{
    float height = 1.0 - texture2D(maps[HEIGHT].texture, uv).r;
    return uv - vec2(V.xy/V.z)*height*maps[HEIGHT].value;
}

vec2 DeepParallax(vec2 uv, vec3 V)
{
    float numLayers = mix(
        float(parallaxMaxLayers),
        float(parallaxMinLayers),
        abs(dot(vec3(0.0, 0.0, 1.0), V)));

    float layerDepth = 1.0/numLayers;
    float currentLayerDepth = 0.0;

    vec2 P = V.xy/V.z*maps[HEIGHT].value;
    vec2 deltaTexCoord = P/numLayers;

    vec2 currentUV = uv;
    float currentDepthMapValue = 1.0 - texture2D(maps[HEIGHT].texture, currentUV).y;
    
    while(currentLayerDepth < currentDepthMapValue)
    {
        currentUV += deltaTexCoord;
        currentLayerDepth += layerDepth;
        currentDepthMapValue = 1.0 - texture2D(maps[HEIGHT].texture, currentUV).y;
    }

    vec2 prevTexCoord = currentUV - deltaTexCoord;
    float afterDepth  = currentDepthMapValue + currentLayerDepth;
    float beforeDepth = 1.0 - texture2D(maps[HEIGHT].texture,
        prevTexCoord).y - currentLayerDepth - layerDepth;

    float weight = afterDepth/(afterDepth - beforeDepth);
    return prevTexCoord*weight + currentUV*(1.0 - weight);
}

float ShadowOmni(int i, float cNdotL)
{
    vec3 fragToLight = fragPosition - lights[i].position;
    float closestDepth = textureCube(lights[i].shadowCubemap, fragToLight).r;
    closestDepth *= farPlane; // Rescale depth
    float currentDepth = length(fragToLight);
    float bias = lights[i].depthBias*max(1.0 - cNdotL, 0.05);
    return currentDepth - bias > closestDepth ? 0.0 : 1.0;
}

float Shadow(int i, float cNdotL)
{
    vec4 p = matLights[i]*vec4(fragPosition, 1.0);

    vec3 projCoords = p.xyz/p.w;
    projCoords = projCoords*0.5 + 0.5;

    float bias = max(lights[i].depthBias*(1.0 - cNdotL), 0.00002) + 0.00001;
    projCoords.z -= bias;

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
            float pcfDepth = texture2D(lights[i].shadowMap, projCoords.xy + vec2(x, y)*lights[i].shadowMapTxlSz).r;
            shadow += step(depth, pcfDepth);
        }
    }

    return shadow/9.0;
}

void main()
{
    // Compute the view direction vector for this fragment
    vec3 V = normalize( viewPos  - fragPosition);

    // Compute fragTexCoord (UV), apply parallax if height map is enabled
    vec2 uv = fragTexCoord;
    if (maps[HEIGHT].active != 0)
    {
        uv = (parallaxMinLayers > 0 && parallaxMaxLayers > 1)
            ? DeepParallax(uv, V) : Parallax(uv, V);

        if (uv.x < 0.0 || uv.y < 0.0 || uv.x > 1.0 || uv.y > 1.0)
        {
            discard;
        }
    }

    // Compute albedo (base color) by sampling the texture and multiplying by the diffuse color
    vec3 albedo = maps[ALBEDO].color.rgb*fragColor.rgb;
    if (maps[ALBEDO].active != 0)
        albedo *= texture2D(maps[ALBEDO].texture, uv).rgb;

    // Compute metallic factor; if a metalness map is used, sample it
    float metalness = maps[METALNESS].value;
    if (maps[METALNESS].active != 0)
        metalness *= texture2D(maps[METALNESS].texture, uv).b;

    // Compute roughness factor; if a roughness map is used, sample it
    float roughness = maps[ROUGHNESS].value;
    if (maps[ROUGHNESS].active != 0)
        roughness *= texture2D(maps[ROUGHNESS].texture, uv).g;

    // Compute F0 (reflectance at normal incidence) based on the metallic factor
    vec3 F0 = ComputeF0(metalness, 0.5, albedo);

    // Compute the normal vector; if a normal map is used, transform it to tangent space
    vec3 N = (maps[NORMAL].active == 0) ? normalize(fragNormal)
        : normalize(TBN*(texture2D(maps[NORMAL].texture, uv).rgb*2.0 - 1.0));

    // Compute the dot product of the normal and view direction
    float NdotV = dot(N, V);
    float cNdotV = max(NdotV, 1e-4);  // Clamped to avoid division by zero

    // Initialize diffuse and specular lighting accumulators
    vec3 diffLighting = vec3(0.0);
    vec3 specLighting = vec3(0.0);

    // Loop through all lights
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        if (lights[i].enabled != 0)
        {
            float size_A = 0.0;
            vec3 L = vec3(0.0);

            // Compute the light direction vector
            if (lights[i].type != DIRLIGHT)
            {
                vec3 LV = lights[i].position - fragPosition;
                L = normalize(LV);

                // If the light has a size, compute the attenuation factor based on the distance
                if (lights[i].size > 0.0)
                {
                    float t = lights[i].size/max(0.001, length(LV));
                    size_A = max(0.0, 1.0 - 1.0/sqrt(1.0 + t*t));
                }
            }
            else
            {
                // For directional lights, use the negative direction as the light direction
                L = normalize(-lights[i].direction);
            }

            // Compute the dot product of the normal and light direction, adjusted by size_A
            float NdotL = min(size_A + dot(N, L), 1.0);
            float cNdotL = max(NdotL, 0.0); // clamped NdotL

            // Compute the halfway vector between the view and light directions
            vec3 H = normalize(V + L);
            float cNdotH = clamp(size_A + dot(N, H), 0.0, 1.0);
            float cLdotH = clamp(size_A + dot(L, H), 0.0, 1.0);

            // Compute light color energy
            vec3 lightColE = lights[i].color*lights[i].energy;

            // Compute diffuse lighting (Burley model) if the material is not fully metallic
            vec3 diffLight = vec3(0.0);
            if (metalness < 1.0)
            {
                float FD90_minus_1 = 2.0*cLdotH*cLdotH*roughness - 0.5;
                float FdV = 1.0 + FD90_minus_1*SchlickFresnel(cNdotV);
                float FdL = 1.0 + FD90_minus_1*SchlickFresnel(cNdotL);

                float diffBRDF = (1.0/PI)*FdV*FdL*cNdotL;
                diffLight = diffBRDF*lightColE;
            }

            // Compute specular lighting using the Schlick-GGX model
            // NOTE: When roughness is 0, specular light should not be entirely disabled.
            // TODO: Handle perfect mirror reflection when roughness is 0.
            vec3 specLight = vec3(0.0);
            if (roughness > 0.0)
            {
                float alphaGGX = roughness*roughness;
                float D = DistributionGGX(cNdotH, alphaGGX);
                float G = GeometrySmith(cNdotL, cNdotV, alphaGGX);

                float cLdotH5 = SchlickFresnel(cLdotH);
                float F90 = clamp(50.0*F0.g, 0.0, 1.0);
                vec3 F = F0 + (F90 - F0)*cLdotH5;

                vec3 specBRDF = cNdotL*D*F*G;
                specLight = specBRDF*lightColE*lights[i].specular;
            }

            // Apply spotlight effect if the light is a spotlight
            float intensity = 1.0;
            if (lights[i].type == SPOTLIGHT)
            {
                float theta = dot(L, normalize(-lights[i].direction));
                float epsilon = (lights[i].innerCutOff - lights[i].outerCutOff);
                intensity = smoothstep(0.0, 1.0, (theta - lights[i].outerCutOff)/epsilon);
            }

            // Apply attenuation based on the distance from the light
            float distance    = length(lights[i].position - fragPosition);
            float attenuation = 1.0/(lights[i].constant +
                                        lights[i].linear*distance +
                                        lights[i].quadratic*(distance*distance));

            // Apply shadow factor if the light casts shadows
            float shadow = 1.0;
            if (lights[i].shadow != 0)
            {
                shadow = (lights[i].type == OMNILIGHT)
                    ? ShadowOmni(i, cNdotL) : Shadow(i, cNdotL);
            }

            // Compute the final intensity factor combining intensity, attenuation, and shadow
            float factor = intensity*attenuation*shadow;

            // Accumulate the diffuse and specular lighting contributions
            diffLighting += diffLight*factor;
            specLighting += specLight*factor;
        }
    }

    // Compute ambient
    vec3 ambient = colAmbient;
    if (cubemaps[IRRADIANCE].active != 0)
    {
        vec3 kS = F0 + (1.0 - F0)*SchlickFresnel(cNdotV);
        vec3 kD = (1.0 - kS)*(1.0 - metalness);
        ambient = kD*textureCube(cubemaps[IRRADIANCE].texture, N).rgb;
    }

    // Compute ambient occlusion
    if (maps[OCCLUSION].active != 0)
    {
        float ao = texture2D(maps[OCCLUSION].texture, uv).r;
        ambient *= ao;

        float lightAffect = mix(1.0, ao, maps[OCCLUSION].value);
        diffLighting *= lightAffect;
        specLighting *= lightAffect;
    }

    // Skybox reflection
    if (cubemaps[CUBEMAP].active != 0)
    {
        vec3 reflectCol = textureCube(cubemaps[CUBEMAP].texture, reflect(-V, N)).rgb;
        specLighting = mix(specLighting, reflectCol, 1.0 - roughness);
    }

    // Compute the final diffuse color, including ambient and diffuse lighting contributions
    vec3 diffuse = albedo*(ambient + diffLighting);

    // Compute emission color; if an emissive map is used, sample it
    vec3 emission = maps[EMISSION].color.rgb;
    if (maps[EMISSION].active != 0)
    {
        emission *= texture2D(maps[EMISSION].texture, uv).rgb;
    }

    // Compute the final fragment color by combining diffuse, specular, and emission contributions
    gl_FragColor = vec4(diffuse + specLighting + emission, 1.0);
};
