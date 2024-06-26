#ifndef RLIGHTS_H
#define RLIGHTS_H

#include <raylib.h>

#ifndef GLSL_VERSION
#   ifdef PLATFORM_DESKTOP
#       define GLSL_VERSION 330
#   else
#       define GLSL_VERSION 100
#   endif //PLATFORM
#endif //GLSL_VERSION

/**
 * @brief Enum representing different types of lights.
 */
typedef enum {
    RLG_DIRECTIONAL,        ///< Enum representing a directional light type.
    RLG_OMNILIGHT,          ///< Enum representing an omnilight type.
    RLG_SPOTLIGHT           ///< Enum representing a spotlight type.
} RLG_LightType;

/**
 * @brief Enum representing different types of shaders.
 */
typedef enum {
    RLG_SHADER_LIGHT,       ///< Enum representing the lighting shader.
    RLG_SHADER_DEPTH,       ///< Enum representing the depth shader.
    RLG_SHADER_SHADOW_MAP   ///< Enum representing the shadow map shader.
} RLG_Shader;

/**
 * @brief Enum representing different types of material maps.
 */
typedef enum {
    RLG_MAP_SPECULAR,       ///< Specular map used for reflecting light.
    RLG_MAP_EMISSIVE,       ///< Emissive map used for emitting light.
    RLG_MAP_NORMAL          ///< Normal map used for bump mapping.
} RLG_MaterialMap;

/**
 * @brief Enum representing different material properties.
 */
typedef enum {
    RLG_MAT_SPECULAR_TINT,  ///< Specular tint property of the material.
    RLG_MAT_EMISSIVE_TINT,  ///< Emissive tint property of the material.
    RLG_MAT_AMBIENT_TINT,   ///< Ambient tint property of the material.
    RLG_MAT_SHININESS       ///< Shininess property of the material.
} RLG_MaterialProperty;

typedef enum {
    RLG_LIGHT_POSITION,
    RLG_LIGHT_DIRECTION,
    RLG_LIGHT_DIFFUSE,
    RLG_LIGHT_SPECULAR_TINT,
    RLG_LIGHT_INNER_CUTOFF,
    RLG_LIGHT_OUTER_CUTOFF,
    RLG_LIGHT_ATTENUATION_CLQ,
    RLG_LIGHT_ATTENUATION_CONSTANT,
    RLG_LIGHT_ATTENUATION_LINEAR,
    RLG_LIGHT_ATTENUATION_QUADRATIC
} RLG_LightProperty;

typedef void* RLG_Context;  ///< Opaque type for a lighting context handle.

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Create a new lighting context with the desired number of lights.
 * 
 * @param lightCount The number of lights to initialize within the context.
 * @return A new RLG_Context object representing the created lighting context.
 */
RLG_Context RLG_CreateContext(unsigned int lightCount);

/**
 * @brief Destroy a previously created lighting context and release associated resources.
 * 
 * @param ctx The lighting context to destroy.
 */
void RLG_DestroyContext(RLG_Context ctx);

/**
 * @brief Set the active lighting context for rlights.
 * 
 * @param ctx The lighting context to set as active.
 */
void RLG_SetContext(RLG_Context ctx);

/**
 * @brief Get the currently active lighting context for rlights.
 * 
 * @return The current RLG_Context object representing the active lighting context.
 */
RLG_Context RLG_GetContext(void);

/**
 * @brief Set custom shader code for a specific shader type.
 * 
 * @note This function should be called before RLG_Init to define your own shaders.
 * 
 * @param shaderType The type of shader to set the custom code for.
 * @param vsCode Vertex shader code for the specified shader type.
 * @param fsCode Fragment shader code for the specified shader type.
 */
void RLG_SetCustomShaderCode(RLG_Shader shaderType, const char *vsCode, const char *fsCode);

/**
 * @brief Get the current shader of the specified type.
 * 
 * @param shaderType The type of shader to retrieve.
 * 
 * @return A pointer to the current Shader object used for the specified shader type.
 *         Returns NULL if the shader type is not loaded.
 */
const Shader* RLG_GetShader(RLG_Shader shaderType);

/**
 * @brief Set the view position, corresponds to the position of your camera.
 * 
 * @param x The x-coordinate of the view position.
 * @param y The y-coordinate of the view position.
 * @param z The z-coordinate of the view position.
 */
void RLG_SetViewPosition(float x, float y, float z);

/**
 * @brief Set the view position using a Vector3 structure.
 * 
 * @param position The view position as a Vector3 structure.
 */
void RLG_SetViewPositionV(Vector3 position);

/**
 * @brief Get the current view position.
 * 
 * @return The current view position as a Vector3 structure.
 */
Vector3 RLG_GetViewPosition(void);

/**
 * @brief Activate or deactivate texture sampling in the materials of models.
 * 
 * @param map The material map to modify.
 * @param active Boolean value indicating whether to activate (true) or deactivate (false) texture sampling.
 */
void RLG_SetMap(RLG_MaterialMap map, bool active);

/**
 * @brief Check if texture sampling is enabled for a given material map.
 * 
 * @param map The material map to check.
 * @return True if texture sampling is enabled, false otherwise.
 */
bool RLG_IsMapEnabled(RLG_MaterialMap map);

/**
 * @brief Set a float value for a specific material property.
 * 
 * @param property The material property to set the value for.
 * @param value The float value to assign to the material property.
 */
void RLG_SetMaterialValue(RLG_MaterialProperty property, float value);

/**
 * @brief Set a color value for a specific material property.
 * 
 * @param property The material property to set the color for.
 * @param color The color to assign to the material property.
 */
void RLG_SetMaterialColor(RLG_MaterialProperty property, Color color);

/**
 * @brief Get the float value of a specific material property.
 * 
 * @param property The material property to retrieve the value from.
 * @return The float value of the specified material property.
 */
float RLG_GetMaterialValue(RLG_MaterialProperty property);

/**
 * @brief Get the color value of a specific material property.
 * 
 * @param property The material property to retrieve the color from.
 * @return The color value of the specified material property.
 */
Color RLG_GetMaterialColor(RLG_MaterialProperty property);

/**
 * @brief Get the number of lights initialized sets in the shader.
 * 
 * @return The number of lights as an unsigned integer.
 */
unsigned int RLG_GetLightcount(void);

/**
 * @brief Activate or deactivate a specific light.
 * 
 * @param light The index of the light to modify.
 * @param active Boolean value indicating whether to activate (true) or deactivate (false) the light.
 */
void RLG_SetLight(unsigned int light, bool active);

/**
 * @brief Check if a specific light is enabled.
 * 
 * @param light The index of the light to check.
 * @return true if the light is enabled, false otherwise.
 */
bool RLG_IsLightEnabled(unsigned int light);

/**
 * @brief Toggle the state of a specific light.
 * 
 * @param light The index of the light to toggle.
 */
void RLG_ToggleLight(unsigned int light);

/**
 * @brief Set the type of a specific light.
 * 
 * @param light The index of the light to set the type for.
 * @param type The type of light to set.
 */
void RLG_SetLightType(unsigned int light, RLG_LightType type);

/**
 * @brief Get the type of a specific light.
 * 
 * @param light The index of the light to get the type for.
 * @return The type of light as RLG_LightType enumeration.
 */
RLG_LightType RLG_GetLightType(unsigned int light);

/**
 * @brief Set a float value for a specific light property.
 * 
 * @param light The index of the light to modify.
 * @param property The light property to set the value for.
 * @param value The float value to assign to the light property.
 */
void RLG_SetLightValue(unsigned int light, RLG_LightProperty property, float value);

/**
 * @brief Set XYZ coordinates for a specific light property.
 * 
 * @param light The index of the light to modify.
 * @param property The light property to set the coordinates for.
 * @param x The X coordinate value.
 * @param y The Y coordinate value.
 * @param z The Z coordinate value.
 */
void RLG_SetLightXYZ(unsigned int light, RLG_LightProperty property, float x, float y, float z);

/**
 * @brief Set a Vector3 value for a specific light property.
 * 
 * @param light The index of the light to modify.
 * @param property The light property to set the Vector3 value for.
 * @param value The Vector3 value to assign to the light property.
 */
void RLG_SetLightVec3(unsigned int light, RLG_LightProperty property, Vector3 value);

/**
 * @brief Set a color value for a specific light property.
 * 
 * @param light The index of the light to modify.
 * @param property The light property to set the color for.
 * @param color The color to assign to the light property.
 */
void RLG_SetLightColor(unsigned int light, RLG_LightProperty property, Color color);

/**
 * @brief Get the float value of a specific light property.
 * 
 * @param light The index of the light to retrieve the value from.
 * @param property The light property to retrieve the value for.
 * @return The float value of the specified light property.
 */
float RLG_GetLightValue(unsigned int light, RLG_LightProperty property);

/**
 * @brief Get the Vector3 value of a specific light property.
 * 
 * @param light The index of the light to retrieve the value from.
 * @param property The light property to retrieve the Vector3 value for.
 * @return The Vector3 value of the specified light property.
 */
Vector3 RLG_GetLightVec3(unsigned int light, RLG_LightProperty property);

/**
 * @brief Get the color value of a specific light property.
 * 
 * @param light The index of the light to retrieve the value from.
 * @param property The light property to retrieve the color value for.
 * @return The color value of the specified light property.
 */
Color RLG_GetLightColor(unsigned int light, RLG_LightProperty property);

/**
 * @brief Translate the position of a specific light by the given offsets.
 * 
 * This function adjusts the position of the specified light by adding the
 * provided x, y, and z offsets to its current position.
 *
 * @param light The index of the light to translate.
 * @param x The offset to add to the x-coordinate of the light position.
 * @param y The offset to add to the y-coordinate of the light position.
 * @param z The offset to add to the z-coordinate of the light position.
 */
void RLG_LightTranslate(unsigned int light, float x, float y, float z);

/**
 * @brief Translate the position of a specific light by the given vector.
 * 
 * This function adjusts the position of the specified light by adding the
 * provided vector to its current position.
 *
 * @param light The index of the light to translate.
 * @param v The vector to add to the light position.
 */
void RLG_LightTranslateV(unsigned int light, Vector3 v);

/**
 * @brief Rotate the direction of a specific light around the X-axis.
 * 
 * This function rotates the direction vector of the specified light by the given
 * degrees around the X-axis.
 *
 * @param light The index of the light to rotate.
 * @param degrees The angle in degrees to rotate the light direction.
 */
void RLG_LightRotateX(unsigned int light, float degrees);

/**
 * @brief Rotate the direction of a specific light around the Y-axis.
 * 
 * This function rotates the direction vector of the specified light by the given
 * degrees around the Y-axis.
 *
 * @param light The index of the light to rotate.
 * @param degrees The angle in degrees to rotate the light direction.
 */
void RLG_LightRotateY(unsigned int light, float degrees);

/**
 * @brief Rotate the direction of a specific light around the Z-axis.
 * 
 * This function rotates the direction vector of the specified light by the given
 * degrees around the Z-axis.
 *
 * @param light The index of the light to rotate.
 * @param degrees The angle in degrees to rotate the light direction.
 */
void RLG_LightRotateZ(unsigned int light, float degrees);

/**
 * @brief Rotate the direction of a specific light around an arbitrary axis.
 * 
 * This function rotates the direction vector of the specified light by the given
 * degrees around the specified axis.
 *
 * @param light The index of the light to rotate.
 * @param axis The axis to rotate around.
 * @param degrees The angle in degrees to rotate the light direction.
 */
void RLG_LightRotate(unsigned int light, Vector3 axis, float degrees);

/**
 * @brief Set the target position of a specific light.
 * 
 * @param light The index of the light to set the target position for.
 * @param x The x-coordinate of the target position.
 * @param y The y-coordinate of the target position.
 * @param z The z-coordinate of the target position.
 */
void RLG_SetLightTarget(unsigned int light, float x, float y, float z);

/**
 * @brief Set the target position of a specific light using a Vector3 structure.
 * 
 * @param light The index of the light to set the target position for.
 * @param targetPosition The target position of the light as a Vector3 structure.
 */
void RLG_SetLightTargetV(unsigned int light, Vector3 targetPosition);

/**
 * @brief Get the target position of a specific light.
 * 
 * @param light The index of the light to get the target position for.
 * @return The target position of the light as a Vector3 structure.
 */
Vector3 RLG_GetLightTarget(unsigned int light);

/**
 * @brief Enable shadow casting for a light.
 *
 * @warning Shadow casting is not fully functional for omnilights yet. Please specify the light direction.
 * 
 * @param light The index of the light to enable shadow casting for.
 * @param shadowMapResolution The resolution of the shadow map.
 * 
 * @todo Implement shadow casting feature for omnilights using cubemaps.
 *       Previous attempts have been made, but it might be optimal to
 *       directly call OpenGL functions bypassing RLGL, though this
 *       approach could pose issues for some users...
 */
void RLG_EnableShadow(unsigned int light, int shadowMapResolution);

/**
 * @brief Disable shadow casting for a light.
 * 
 * @param light The index of the light to disable shadow casting for.
 */
void RLG_DisableShadow(unsigned int light);

/**
 * @brief Check if shadow casting is enabled for a light.
 * 
 * @param light The index of the light to check for shadow casting.
 * @return true if shadow casting is enabled, false otherwise.
 */
bool RLG_IsShadowEnabled(unsigned int light);

/**
 * @brief Set the bias value for shadow mapping of a light.
 * 
 * @param light The index of the light to set the shadow bias for.
 * @param value The bias value to set.
 */
void RLG_SetShadowBias(unsigned int light, float value);

/**
 * @brief Get the bias value for shadow mapping of a light.
 * 
 * @param light The index of the light to get the shadow bias for.
 * @return The shadow bias value.
 */
float RLG_GetShadowBias(unsigned int light);

/**
 * @brief Begin shadow casting for a specific light.
 * 
 * @param light The index of the light to begin shadow casting for.
 */
void RLG_BeginShadowCast(unsigned int light);

/**
 * @brief End shadow casting for the current light.
 */
void RLG_EndShadowCast(void);

/**
 * @brief Clear the shadow map.
 * 
 * This function clears the shadow map, removing any existing shadow data.
 */
void RLG_ClearShadowMap(void);

/**
 * @brief Draw the shadow map of a specific light.
 * 
 * This function draws the shadow map of the specified light to the screen.
 * 
 * @param light The index of the light whose shadow map to draw.
 * @param x The x-coordinate of the top-left corner of the shadow map rectangle.
 * @param y The y-coordinate of the top-left corner of the shadow map rectangle.
 * @param w The width of the shadow map rectangle.
 * @param h The height of the shadow map rectangle.
 */
void RLG_DrawShadowMap(unsigned int light, int x, int y, int w, int h);

/**
 * @brief Draw the shadow map of a specific light with extended parameters.
 * 
 * This function draws the shadow map of the specified light to the screen with additional parameters for near and far distances.
 * 
 * @param light The index of the light whose shadow map to draw.
 * @param x The x-coordinate of the top-left corner of the shadow map rectangle.
 * @param y The y-coordinate of the top-left corner of the shadow map rectangle.
 * @param w The width of the shadow map rectangle.
 * @param h The height of the shadow map rectangle.
 * @param near The near clipping plane distance.
 * @param far The far clipping plane distance.
 */
void RLG_DrawShadowMapEx(unsigned int light, int x, int y, int w, int h, float near, float far);

/**
 * @brief Cast a mesh for shadow rendering.
 * 
 * This function casts a mesh in the active shadow map for shadow rendering with the specified transformation.
 * 
 * @param mesh The mesh to cast.
 * @param transform The transformation matrix to apply to the mesh.
 */
void RLG_CastMesh(Mesh mesh, Matrix transform);

/**
 * @brief Cast a model for shadow rendering.
 * 
 * This function casts a model in the active shadow map for shadow rendering at the specified position and scale.
 * 
 * @param model The model to cast.
 * @param position The position at which to cast the model for shadow rendering.
 * @param scale The scale at which to cast the model for shadow rendering.
 */
void RLG_CastModel(Model model, Vector3 position, float scale);

/**
 * @brief Cast a model into for shadow rendering with extended parameters.
 * 
 * This function casts a model in the active shadow map for shadow rendering at the specified position, rotation, and scale.
 * 
 * @param model The model to cast.
 * @param position The position at which to cast the model for shadow rendering.
 * @param rotationAxis The axis around which to rotate the model for shadow rendering.
 * @param rotationAngle The angle by which to rotate the model for shadow rendering.
 * @param scale The scale at which to cast the model for shadow rendering.
 */
void RLG_CastModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale);

/**
 * @brief Draw a mesh with a specified material and transformation.
 * 
 * This function draws a mesh with the specified material and transformation.
 * 
 * @param mesh The mesh to draw.
 * @param material The material to apply to the mesh.
 * @param transform The transformation matrix to apply to the mesh.
 */
void RLG_DrawMesh(Mesh mesh, Material material, Matrix transform);

/**
 * @brief Draw a model at a specified position with a specified scale and tint.
 * 
 * This function draws a model at the specified position with the specified scale and tint.
 * 
 * @param model The model to draw.
 * @param position The position at which to draw the model.
 * @param scale The scale at which to draw the model.
 * @param tint The tint color to apply to the model.
 */
void RLG_DrawModel(Model model, Vector3 position, float scale, Color tint);

/**
 * @brief Draw a model at a specified position with a specified rotation, scale, and tint.
 * 
 * This function draws a model at the specified position with the specified rotation, scale, and tint.
 * 
 * @param model The model to draw.
 * @param position The position at which to draw the model.
 * @param rotationAxis The axis around which to rotate the model.
 * @param rotationAngle The angle by which to rotate the model.
 * @param scale The scale at which to draw the model.
 * @param tint The tint color to apply to the model.
 */
void RLG_DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);

#if defined(__cplusplus)
}
#endif

#ifdef RLIGHTS_IMPLEMENTATION

#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include <rlgl.h>

#ifndef NO_EMBEDDED_SHADERS

#define STRINGIFY(x) #x             ///< Undef after shader definitions
#define TOSTRING(x) STRINGIFY(x)    ///< Undef after shader definitions

#define GLSL_VERSION_DEF \
    "#version " TOSTRING(GLSL_VERSION) "\n"

#if GLSL_VERSION < 330

#   define GLSL_TEXTURE_DEF     "#define TEX texture2D\n"
#   define GLSL_FS_OUT_DEF      ""

#   define GLSL_FINAL_COLOR(x)  "gl_FragColor = " x ";"
#   define GLSL_PRECISION(x)    "precision " x ";"

#   define GLSL_VS_IN(x)        "attribute " x ";"
#   define GLSL_FS_IN(x)        "varying " x ";"
#   define GLSL_VS_OUT(x)       "varying " x ";"

#   define GLSL_FS_FLAT_IN(x)   "varying " x ";"
#   define GLSL_VS_FLAT_OUT(x)  "varying " x ";"

#else

#   define GLSL_TEXTURE_DEF     "#define TEX texture\n"
#   define GLSL_FS_OUT_DEF      "out vec4 _;"

#   define GLSL_FINAL_COLOR(x)  "_ = " x ";"
#   define GLSL_PRECISION(x)    ""

#   define GLSL_VS_IN(x)        "in " x ";"
#   define GLSL_FS_IN(x)        "in " x ";"
#   define GLSL_VS_OUT(x)       "out " x ";"

#   define GLSL_FS_FLAT_IN(x)   "flat in " x ";"
#   define GLSL_VS_FLAT_OUT(x)  "flat out " x ";"

#endif

/* Shader */

static const char rlgLightVS[] = GLSL_VERSION_DEF

#   if GLSL_VERSION > 100
    "#define NUM_LIGHTS %i\n"
    "uniform mat4 matLights[NUM_LIGHTS];"
    GLSL_VS_OUT("vec4 fragPosLightSpace[NUM_LIGHTS]")
#   endif

    GLSL_VS_IN("vec3 vertexPosition")
    GLSL_VS_IN("vec2 vertexTexCoord")
    GLSL_VS_IN("vec4 vertexTangent")
    GLSL_VS_IN("vec3 vertexNormal")
    GLSL_VS_IN("vec4 vertexColor")

    "uniform lowp int useNormalMap;"
    "uniform mat4 matNormal;"
    "uniform mat4 matModel;"
    "uniform mat4 mvp;"

    GLSL_VS_OUT("vec3 fragPosition")
    GLSL_VS_OUT("vec2 fragTexCoord")
    GLSL_VS_OUT("vec3 fragNormal")
    GLSL_VS_OUT("vec4 fragColor")
    GLSL_VS_FLAT_OUT("mat3 TBN")

    "void main()"
    "{"
        "fragPosition = vec3(matModel*vec4(vertexPosition, 1.0));"
        "fragNormal = (matNormal*vec4(vertexNormal, 0.0)).xyz;"

        "fragTexCoord = vertexTexCoord;"
        "fragColor = vertexColor;"

        "if (useNormalMap != 0)"
        "{"
            "vec3 T = normalize(vec3(matModel*vec4(vertexTangent.xyz, 0.0)));"
            "vec3 B = cross(fragNormal, T)*vertexTangent.w;"
            "TBN = mat3(T, B, fragNormal);"
        "}"

#       if GLSL_VERSION > 100
        "for (int i = 0; i < NUM_LIGHTS; i++)"
        "{"
            "fragPosLightSpace[i] = matLights[i]*vec4(fragPosition, 1.0);"
        "}"
#       endif

        "gl_Position = mvp*vec4(vertexPosition, 1.0);"
    "}";

static const char rlgLightFS[] = GLSL_VERSION_DEF GLSL_TEXTURE_DEF

    "#define NUM_LIGHTS %i\n"

    "#define DIRLIGHT 0\n"
    "#define OMNILIGHT 1\n"
    "#define SPOTLIGHT 2\n"

    GLSL_PRECISION("mediump float")

#   if GLSL_VERSION > 100
    GLSL_FS_IN("vec4 fragPosLightSpace[NUM_LIGHTS]")
#   else
    "uniform mat4 matLights[NUM_LIGHTS];"
#   endif

    GLSL_FS_IN("vec3 fragPosition")
    GLSL_FS_IN("vec2 fragTexCoord")
    GLSL_FS_IN("vec3 fragNormal")
    GLSL_FS_IN("vec4 fragColor")
    GLSL_FS_FLAT_IN("mat3 TBN")

    GLSL_FS_OUT_DEF

    "struct Light {"
        "sampler2D shadowMap;"      ///< Sampler for the shadow map texture
        "vec3 position;"            ///< Position of the light in world coordinates
        "vec3 direction;"           ///< Direction vector of the light (for directional and spotlights)
        "vec3 diffuse;"             ///< Diffuse color of the light
        "vec3 specular;"            ///< Specular color of the light
        "float innerCutOff;"        ///< Inner cutoff angle for spotlights (cosine of the angle)
        "float outerCutOff;"        ///< Outer cutoff angle for spotlights (cosine of the angle)
        "float constant;"           ///< Constant attenuation factor
        "float linear;"             ///< Linear attenuation factor
        "float quadratic;"          ///< Quadratic attenuation factor
        "float shadowMapTxlSz;"     ///< Texel size of the shadow map
        "float depthBias;"          ///< Bias value to avoid self-shadowing artifacts
        "lowp int type;"            ///< Type of the light (e.g., point, directional, spotlight)
        "lowp int shadow;"          ///< Indicates if the light casts shadows (1 for true, 0 for false)
        "lowp int enabled;"         ///< Indicates if the light is active (1 for true, 0 for false)
    "};"

    "uniform Light lights[NUM_LIGHTS];"

    "uniform lowp int useSpecularMap;"
    "uniform lowp int useEmissiveMap;"
    "uniform lowp int useNormalMap;"

    "uniform sampler2D texture0;"   // diffuse
    "uniform sampler2D texture1;"   // specular
    "uniform sampler2D texture2;"   // normal
    "uniform sampler2D texture5;"   // emissive

    "uniform vec3 colSpecular;"     // sent by rlights
    "uniform vec3 colEmissive;"     // sent by rlights
    "uniform vec4 colDiffuse;"      // sent by raylib
    "uniform vec3 colAmbient;"      // sent by rlights

    "uniform float shininess;"
    "uniform vec3 viewPos;"

    "float ShadowCalc(int i)"
    "{"
#       if GLSL_VERSION > 100
        "vec4 p = fragPosLightSpace[i];"
#       else
        "vec4 p = matLights[i]*vec4(fragPosition, 1.0);"
#       endif

        "vec3 projCoords = p.xyz/p.w;"
        "projCoords = projCoords*0.5 + 0.5;"
        "projCoords.z -= lights[i].depthBias;"

        "if (projCoords.z > 1.0 || projCoords.x > 1.0 || projCoords.y > 1.0)"
        "{"
            "return 1.0;"
        "}"

        "float depth = projCoords.z;"
        "float shadow = 0.0;"

        // NOTE: You can increase iterations to improve PCF quality
        "for (int x = -1; x <= 1; x++)"
        "{"
            "for (int y = -1; y <= 1; y++)"
            "{"
                "float pcfDepth = TEX(lights[i].shadowMap, projCoords.xy + vec2(x, y)*lights[i].shadowMapTxlSz).r; "
                "shadow += step(depth, pcfDepth);"
            "}"
        "}"

        "return shadow/9.0;"
    "}"

    "void main()"
    "{"
        // get texture samples
        "vec3 diffSample = TEX(texture0, fragTexCoord).rgb*colDiffuse.rgb*fragColor.rgb;"
        "vec3 specSample = (useSpecularMap != 0) ? TEX(texture1, fragTexCoord).rgb*colSpecular : colSpecular;"

        // compute normals
        "vec3 normal;"
        "if (useNormalMap == 0) normal = normalize(fragNormal);"
        "else normal = normalize(TBN*(TEX(texture2, fragTexCoord).rgb*2.0 - 1.0));"

        // compute current view dir for this frag
        "vec3 viewDir = normalize(viewPos - fragPosition);"

        // process lights
        "vec3 finalColor = vec3(0.0);"
        "for (int i = 0; i < NUM_LIGHTS; i++)"
        "{"
            "if (lights[i].enabled != 0)"
            "{"
                // get lightDir
                "vec3 lightDir = (lights[i].type != DIRLIGHT)"
                    "? normalize(lights[i].position - fragPosition)"
                    ": normalize(-lights[i].direction);"

                // diffuse
                "float diff = max(dot(normal, lightDir), 0.0);"
                "vec3 diffuse = lights[i].diffuse*diffSample*diff;"

                // specular (Blinn-Phong)
                "vec3 halfwayDir = normalize(lightDir + viewDir);"
                "float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);"
                "vec3 specular = lights[i].specular*specSample*spec;"

                // spotlight
                "float intensity = 1.0;"
                "if (lights[i].type == SPOTLIGHT)"
                "{"
                    "float theta = dot(lightDir, normalize(-lights[i].direction));"
                    "float epsilon = (lights[i].innerCutOff - lights[i].outerCutOff);"
                    "intensity = smoothstep(0.0, 1.0, (theta - lights[i].outerCutOff) / epsilon);"
                "}"

                // attenuation
                "float distance    = length(lights[i].position - fragPosition);"
                "float attenuation = 1.0/(lights[i].constant + lights[i].linear*distance + lights[i].quadratic*(distance*distance));"

                // shadow
                "float shadow = (lights[i].shadow != 0) ? ShadowCalc(i) : 1.0;"

                // add final light color
                "finalColor += (diffuse + specular)*intensity*attenuation*shadow;"
            "}"
        "}"

        // compute ambient
        "vec3 ambientColor = colAmbient*diffSample;"

        // compute emission
        "vec3 emission = colEmissive;"
        "if (useEmissiveMap != 0)"
        "{"
            "emission *= TEX(texture5, fragTexCoord).rgb;"
        "}"

        // compute final color
        GLSL_FINAL_COLOR("vec4(ambientColor + finalColor + emission, 1.0)")
    "}";

static const char rlgDepthVS[] = GLSL_VERSION_DEF
    GLSL_VS_IN("vec3 vertexPosition")
    "uniform mat4 mvp;"
    "void main()"
    "{"
        "gl_Position = mvp*vec4(vertexPosition, 1.0);"
    "}";

static const char rlgDepthFS[] = GLSL_VERSION_DEF
    GLSL_PRECISION("mediump float")
    GLSL_FS_OUT_DEF
    "void main()"
    "{"
        //"gl_FragDepth = gl_FragCoord.z;" ///< Seems to cause problems on some hardware
        GLSL_FINAL_COLOR("vec4(gl_FragCoord.z)")
    "}";

static const char rlgShadowMapFS[] = GLSL_VERSION_DEF GLSL_TEXTURE_DEF
    GLSL_PRECISION("mediump float")
    GLSL_FS_IN("vec2 fragTexCoord")
    "uniform sampler2D texture0;"
    "uniform float near;"
    "uniform float far;"
    GLSL_FS_OUT_DEF
    "void main()"
    "{"
        "float depth = TEX(texture0, vec2(fragTexCoord.x, 1.0 - fragTexCoord.y)).r;"
        "depth = (2.0*near*far)/(far + near - (depth*2.0 - 1.0)*(far - near));"
        GLSL_FINAL_COLOR("vec4(vec3(depth/far), 1.0)")
    "}";

#undef TOSTRING
#undef STRINGIFY

#endif //NO_EMBEDDED_SHADERS

/* Types definitions */

struct RLG_GlobalLightLocs
{
    int colSpecular;
    int colEmissive;
    int colAmbient;

    int viewPos;
    int shininess;

    int useSpecularMap;
    int useEmissiveMap;
    int useNormalMap;
};

struct RLG_GlobalLight
{
    Vector3 colSpecular;
    Vector3 colEmissive;
    Vector3 colAmbient;

    Vector3 viewPos;
    float shininess;

    int useSpecularMap;
    int useEmissiveMap;
    int useNormalMap;
};

struct RLG_ShadowMap
{
    Texture2D depth;
    unsigned int id;
    int width, height;
};

struct RLG_LightLocs
{
    int vpMatrix;       ///< NOTE: Not present in the Light struct but in a separate uniform
    int shadowMap;
    int position;
    int direction;
    int diffuse;
    int specular;
    int innerCutOff;
    int outerCutOff;
    int constant;
    int linear;
    int quadratic;
    int shadowMapTxlSz;
    int depthBias;
    int type;
    int shadow;
    int enabled;
};

struct RLG_Light
{
    struct RLG_ShadowMap shadowMap;
    Vector3 position;
    Vector3 direction;
    Vector3 diffuse;
    Vector3 specular;
    float innerCutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    float shadowMapTxlSz;
    float depthBias;
    int type;
    int shadow;
    int enabled;
};

struct RLG_ShadowMapShaderData
{
    float near, far;
    int locNear, locFar;
};

static struct RLG_Core
{
    struct RLG_GlobalLightLocs locsGlobalLight;
    struct RLG_GlobalLight globalLight;
    struct RLG_LightLocs *locsLights;
    struct RLG_Light *lights;
    int lightCount;

    struct RLG_ShadowMapShaderData
    shadowMapShaderData;

    Shader lightShader;
    Shader depthShader;
    Shader shadowMapShader;
}
*rlgCtx = NULL;

#ifndef NO_EMBEDDED_SHADERS
    static const char
        *rlgCachedLightVS = rlgLightVS,
        *rlgCachedLightFS = rlgLightFS;
    static const char
        *rlgCachedDepthVS = rlgDepthVS,
        *rlgCachedDepthFS = rlgDepthFS;
    static const char
        *rlgCachedShadowMapVS = NULL,
        *rlgCachedShadowMapFS = rlgShadowMapFS;
#else
    static const char
        *rlgCachedLightVS       = NULL,
        *rlgCachedLightFS       = NULL,
        *rlgCachedDepthVS       = NULL,
        *rlgCachedDepthFS       = NULL,
        *rlgCachedShadowMapVS   = NULL,
        *rlgCachedShadowMapFS   = NULL;
#endif //NO_EMBEDDED_SHADERS

/* Public API */

RLG_Context RLG_CreateContext(unsigned int count)
{
    struct RLG_Core *rlgCtx = (struct RLG_Core*)malloc(sizeof(struct RLG_Core));

    if (!rlgCtx)
    {
        TraceLog(LOG_FATAL, "Heap allocation for RLG context failed!");
        return NULL;
    }

    // NOTE: The limit of 99 is because we measure the size of `rlgLightFS` with '%s'
    if (count > 99)
    {
        TraceLog(LOG_WARNING, "The limit of lights supported by rlights is 99."
                              "The number of lights has therefore been adjusted to this value.");
        count = 99;
    }

    // We check if all the shader codes are well defined
    if (rlgCachedLightVS == NULL) TraceLog(LOG_WARNING, "The lighting vertex shader has not been defined.");
    if (rlgCachedLightFS == NULL) TraceLog(LOG_WARNING, "The lighting fragment shader has not been defined.");
    if (rlgCachedDepthVS == NULL) TraceLog(LOG_WARNING, "The depth vertex shader has not been defined.");
    if (rlgCachedDepthFS == NULL) TraceLog(LOG_WARNING, "The depth fragment shader has not been defined.");

    const char *lightVS = rlgCachedLightVS;
    const char *lightFS = rlgCachedLightFS;

#   ifndef NO_EMBEDDED_SHADERS

#       if GLSL_VERSION > 100
        bool vsFormated = (lightVS == rlgLightVS);
        if (vsFormated)
        {
            // Format frag shader with lights count
            char *fmtVert = (char*)malloc(sizeof(rlgLightVS));
            snprintf(fmtVert, sizeof(rlgLightVS), rlgLightVS, count);
            lightVS = fmtVert;
        }
#       endif

        bool fsFormated = (lightFS == rlgLightFS);
        if (fsFormated)
        {
            // Format frag shader with lights count
            char *fmtFrag = (char*)malloc(sizeof(rlgLightFS));
            snprintf(fmtFrag, sizeof(rlgLightFS), rlgLightFS, count);
            lightFS = fmtFrag;
        }

#   endif //NO_EMBEDDED_SHADERS

    // Load shader and get locations
    rlgCtx->lightShader = LoadShaderFromMemory(lightVS, lightFS);

#   ifndef NO_EMBEDDED_SHADERS
#   if GLSL_VERSION > 100
    if (vsFormated) free((void*)lightVS);
#   endif
    if (fsFormated) free((void*)lightFS);
#   endif //NO_EMBEDDED_SHADERS

    // Retrieving global shader locations
    rlgCtx->locsGlobalLight.useSpecularMap = GetShaderLocation(rlgCtx->lightShader, "useSpecularMap");
    rlgCtx->locsGlobalLight.useEmissiveMap = GetShaderLocation(rlgCtx->lightShader, "useEmissiveMap");
    rlgCtx->locsGlobalLight.useNormalMap = GetShaderLocation(rlgCtx->lightShader, "useNormalMap");
    rlgCtx->locsGlobalLight.colSpecular = GetShaderLocation(rlgCtx->lightShader, "colSpecular");
    rlgCtx->locsGlobalLight.colEmissive = GetShaderLocation(rlgCtx->lightShader, "colEmissive");
    rlgCtx->locsGlobalLight.colAmbient = GetShaderLocation(rlgCtx->lightShader, "colAmbient");
    rlgCtx->locsGlobalLight.shininess = GetShaderLocation(rlgCtx->lightShader, "shininess");
    rlgCtx->locsGlobalLight.viewPos = GetShaderLocation(rlgCtx->lightShader, "viewPos");

    // Define default global uniforms
    rlgCtx->globalLight = (struct RLG_GlobalLight) { 0 };
    rlgCtx->globalLight.colSpecular = (Vector3) { 1.0f, 1.0f, 1.0f };
    rlgCtx->globalLight.colEmissive = (Vector3) { 0.0f, 0.0f, 0.0f };
    rlgCtx->globalLight.colAmbient = (Vector3) { 0.1f, 0.1f, 0.1f };
    rlgCtx->globalLight.shininess = 32.0f;

    // Send default globals uniforms (no need to send zero-values)
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colSpecular, &rlgCtx->globalLight.colSpecular, SHADER_UNIFORM_VEC3);
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colAmbient, &rlgCtx->globalLight.colAmbient, SHADER_UNIFORM_VEC3);
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.shininess, &rlgCtx->globalLight.shininess, SHADER_UNIFORM_FLOAT);

    // Allocation and initialization of the desired number of lights
    rlgCtx->lights = (struct RLG_Light*)malloc(count*sizeof(struct RLG_Light));
    rlgCtx->locsLights = (struct RLG_LightLocs*)malloc(count*sizeof(struct RLG_LightLocs));
    for (int i = 0; i < count; i++)
    {
        struct RLG_Light *light = &rlgCtx->lights[i];
        struct RLG_LightLocs *locs = &rlgCtx->locsLights[i];

        *light = (struct RLG_Light) {
            .shadowMap      = (struct RLG_ShadowMap) { 0 },
            .position       = (Vector3) { 0 },
            .direction      = (Vector3) { 0 },
            .diffuse        = (Vector3) { 1.0f, 1.0f, 1.0f },
            .specular       = (Vector3) { 1.0f, 1.0f, 1.0f },
            .innerCutOff    = -1.0f,
            .outerCutOff    = -1.0f,
            .constant       = 1.0f,
            .linear         = 0.0f,
            .quadratic      = 0.0f,
            .shadowMapTxlSz = 0.0f,
            .depthBias      = 0.0f,
            .type           = RLG_DIRECTIONAL,
            .shadow         = 0,
            .enabled        = 0
        };

        locs->vpMatrix       = GetShaderLocation(rlgCtx->lightShader, TextFormat("matLights[%i]", i));
        locs->shadowMap      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].shadowMap", i));
        locs->position       = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].position", i));
        locs->direction      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].direction", i));
        locs->diffuse        = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].diffuse", i));
        locs->specular       = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].specular", i));
        locs->innerCutOff    = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].innerCutOff", i));
        locs->outerCutOff    = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].outerCutOff", i));
        locs->constant       = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].constant", i));
        locs->linear         = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].linear", i));
        locs->quadratic      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].quadratic", i));
        locs->shadowMapTxlSz = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].shadowMapTxlSz", i));
        locs->depthBias      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].depthBias", i));
        locs->type           = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].type", i));
        locs->shadow         = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].shadow", i));
        locs->enabled        = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].enabled", i));

        SetShaderValue(rlgCtx->lightShader, locs->diffuse, &light->diffuse, SHADER_UNIFORM_VEC3);
        SetShaderValue(rlgCtx->lightShader, locs->specular, &light->specular, SHADER_UNIFORM_VEC3);
        SetShaderValue(rlgCtx->lightShader, locs->innerCutOff, &light->innerCutOff, SHADER_UNIFORM_FLOAT);
        SetShaderValue(rlgCtx->lightShader, locs->outerCutOff, &light->outerCutOff, SHADER_UNIFORM_FLOAT);
        SetShaderValue(rlgCtx->lightShader, locs->constant, &light->constant, SHADER_UNIFORM_FLOAT);
    }

    // Set light count
    rlgCtx->lightCount = count;

    // Load depth shader (used for shadow casting)
    rlgCtx->depthShader = LoadShaderFromMemory(rlgCachedDepthVS, rlgCachedDepthFS);

    // Load shadow map shader (used to render shadow maps)
    rlgCtx->shadowMapShader = LoadShaderFromMemory(rlgCachedShadowMapVS, rlgCachedShadowMapFS);

    rlgCtx->shadowMapShaderData.near = 0.1f;
    rlgCtx->shadowMapShaderData.far = 100.0f;

    rlgCtx->shadowMapShaderData.locNear = GetShaderLocation(rlgCtx->shadowMapShader, "near");
    rlgCtx->shadowMapShaderData.locFar = GetShaderLocation(rlgCtx->shadowMapShader, "far");

    SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->shadowMapShaderData.locNear,
        &rlgCtx->shadowMapShaderData.near, SHADER_UNIFORM_FLOAT);

    SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->shadowMapShaderData.locFar,
        &rlgCtx->shadowMapShaderData.far, SHADER_UNIFORM_FLOAT);

    return (RLG_Context)rlgCtx;
}

void RLG_DestroyContext(RLG_Context ctx)
{
    struct RLG_Core *pCtx = (struct RLG_Core*)ctx;

    if (IsShaderReady(pCtx->lightShader))
    {
        UnloadShader(pCtx->lightShader);
        pCtx->lightShader = (Shader) { 0 };
    }

    if (IsShaderReady(pCtx->depthShader))
    {
        UnloadShader(pCtx->depthShader);
        pCtx->depthShader = (Shader) { 0 };
    }

    if (IsShaderReady(pCtx->shadowMapShader))
    {
        UnloadShader(pCtx->shadowMapShader);
        pCtx->shadowMapShader = (Shader) { 0 };
    }

    if (pCtx->lights != NULL)
    {
        for (int i = 0; i < pCtx->lightCount; i++)
        {
            if (pCtx->lights[i].shadowMap.id != 0)
            {
                rlUnloadTexture(pCtx->lights[i].shadowMap.depth.id);
                rlUnloadFramebuffer(pCtx->lights[i].shadowMap.id);
            }
        }

        free(pCtx->lights);
        pCtx->lights = NULL;
    }

    if (pCtx->locsLights != NULL)
    {
        free(pCtx->locsLights);
        pCtx->locsLights = NULL;
    }

    pCtx->lightCount = 0;
}

void RLG_SetContext(RLG_Context ctx)
{
    rlgCtx = (struct RLG_Core*)ctx;
}

RLG_Context RLG_GetContext(void)
{
    return (RLG_Context)rlgCtx;
}

void RLG_SetCustomShaderCode(RLG_Shader shaderType, const char *vsCode, const char *fsCode)
{
    switch (shaderType)
    {
        case RLG_SHADER_LIGHT:
            rlgCachedLightVS = vsCode;
            rlgCachedLightFS = fsCode;
            break;

        case RLG_SHADER_DEPTH:
            rlgCachedDepthVS = vsCode;
            rlgCachedDepthFS = fsCode;
            break;

        case RLG_SHADER_SHADOW_MAP:
            rlgCachedShadowMapVS = vsCode;
            rlgCachedShadowMapFS = fsCode;
            break;

        default:
            TraceLog(LOG_WARNING, "Unsupported 'shaderType' passed to 'RLG_SetCustomShader'");
            break;
    }
}

const Shader* RLG_GetShader(RLG_Shader shaderType)
{
    switch (shaderType)
    {
        case RLG_SHADER_LIGHT:
            return IsShaderReady(rlgCtx->lightShader) ? &rlgCtx->lightShader: NULL;

        case RLG_SHADER_DEPTH:
            return IsShaderReady(rlgCtx->depthShader) ? &rlgCtx->depthShader: NULL;

        case RLG_SHADER_SHADOW_MAP:
            return IsShaderReady(rlgCtx->shadowMapShader) ? &rlgCtx->shadowMapShader: NULL;

        default:
            break;
    }

    return NULL;
}

void RLG_SetViewPosition(float x, float y, float z)
{
    RLG_SetViewPositionV((Vector3) { x, y, z });
}

void RLG_SetViewPositionV(Vector3 position)
{
    rlgCtx->globalLight.viewPos = position;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.viewPos,
        &rlgCtx->globalLight.viewPos, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetViewPosition(void)
{
    return rlgCtx->globalLight.viewPos;
}

void RLG_SetMap(RLG_MaterialMap map, bool active)
{
    int v = (int)active;

    switch (map)
    {
        case RLG_MAP_SPECULAR:
            rlgCtx->globalLight.useSpecularMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.useSpecularMap, &v, SHADER_UNIFORM_INT);
            break;

        case RLG_MAP_EMISSIVE:
            rlgCtx->globalLight.useEmissiveMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.useEmissiveMap, &v, SHADER_UNIFORM_INT);
            break;

        case RLG_MAP_NORMAL:
            rlgCtx->globalLight.useNormalMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.useNormalMap, &v, SHADER_UNIFORM_INT);
            break;

        default:
            break;
    }
}

bool RLG_IsMapEnabled(RLG_MaterialMap map)
{
    switch (map)
    {
        case RLG_MAP_SPECULAR:
            return rlgCtx->globalLight.useSpecularMap;

        case RLG_MAP_EMISSIVE:
            return rlgCtx->globalLight.useEmissiveMap;

        case RLG_MAP_NORMAL:
            return rlgCtx->globalLight.useNormalMap;

        default:
            break;
    }

    return false;
}

void RLG_SetMaterialValue(RLG_MaterialProperty property, float value)
{
    switch (property)
    {
        case RLG_MAT_SPECULAR_TINT:
            rlgCtx->globalLight.colSpecular = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colSpecular,
                &rlgCtx->globalLight.colSpecular, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_EMISSIVE_TINT:
            rlgCtx->globalLight.colEmissive = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colEmissive,
                &rlgCtx->globalLight.colEmissive, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_AMBIENT_TINT:
            rlgCtx->globalLight.colAmbient = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colAmbient,
                &rlgCtx->globalLight.colAmbient, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_SHININESS:
            rlgCtx->globalLight.shininess = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.shininess,
                &value, SHADER_UNIFORM_FLOAT);
            break;

        default:
            break;
    }
}

void RLG_SetMaterialColor(RLG_MaterialProperty property, Color color)
{
    Vector3 nCol = (Vector3) {
        (float)color.r/255,
        (float)color.g/255,
        (float)color.b/255
    };

    switch (property)
    {
        case RLG_MAT_SPECULAR_TINT:
            rlgCtx->globalLight.colSpecular = nCol;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colSpecular,
                &nCol, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_EMISSIVE_TINT:
            rlgCtx->globalLight.colEmissive = nCol;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colEmissive,
                &nCol, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_AMBIENT_TINT:
            rlgCtx->globalLight.colAmbient = nCol;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsGlobalLight.colAmbient,
                &nCol, SHADER_UNIFORM_VEC3);
            break;

        default:
            break;
    }
}

float RLG_GetMaterialValue(RLG_MaterialProperty property)
{
    switch (property)
    {
        case RLG_MAT_SHININESS:
            return rlgCtx->globalLight.shininess;

        default:
            break;
    }

    return 0;
}

Color RLG_GetMaterialColor(RLG_MaterialProperty property)
{
    Color result = BLACK;

    switch (property)
    {
        case RLG_MAT_SPECULAR_TINT:
            result.r = (unsigned char)(255*rlgCtx->globalLight.colSpecular.x);
            result.g = (unsigned char)(255*rlgCtx->globalLight.colSpecular.y);
            result.b = (unsigned char)(255*rlgCtx->globalLight.colSpecular.z);
            break;

        case RLG_MAT_EMISSIVE_TINT:
            result.r = (unsigned char)(255*rlgCtx->globalLight.colEmissive.x);
            result.g = (unsigned char)(255*rlgCtx->globalLight.colEmissive.y);
            result.b = (unsigned char)(255*rlgCtx->globalLight.colEmissive.z);
            break;

        case RLG_MAT_AMBIENT_TINT:
            result.r = (unsigned char)(255*rlgCtx->globalLight.colAmbient.x);
            result.g = (unsigned char)(255*rlgCtx->globalLight.colAmbient.y);
            result.b = (unsigned char)(255*rlgCtx->globalLight.colAmbient.z);
            break;

        default:
            break;
    }

    return result;
}

unsigned int RLG_GetLightcount(void)
{
    return rlgCtx->lightCount;
}

void RLG_SetLight(unsigned int light, bool active)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLight' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    rlgCtx->lights[light].enabled = (int)active;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].enabled,
        &rlgCtx->lights[light].enabled, SHADER_UNIFORM_INT);
}

bool RLG_IsLightEnabled(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_IsLightEnabled' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return false;
    }

    return (bool)rlgCtx->lights[light].enabled;
}

void RLG_ToggleLight(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_ToggleLight' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    rlgCtx->lights[light].enabled = !rlgCtx->lights[light].enabled;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].enabled,
        &rlgCtx->lights[light].enabled, SHADER_UNIFORM_INT);
}

void RLG_SetLightType(unsigned int light, RLG_LightType type)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightType' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    rlgCtx->lights[light].type = (int)type;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].type,
        &rlgCtx->lights[light].type, SHADER_UNIFORM_INT);
}

RLG_LightType RLG_GetLightType(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightType' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return (RLG_LightType)0;
    }

    return (RLG_LightType)rlgCtx->lights[light].type;
}

void RLG_SetLightValue(unsigned int light, RLG_LightProperty property, float value)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightValue' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    switch (property)
    {
        case RLG_LIGHT_DIFFUSE:
            rlgCtx->lights[light].diffuse = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].diffuse,
                &rlgCtx->lights[light].diffuse, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_SPECULAR_TINT:
            rlgCtx->lights[light].specular = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].specular,
                &rlgCtx->lights[light].specular, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_INNER_CUTOFF:
            rlgCtx->lights[light].innerCutOff = cosf(value*DEG2RAD);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].innerCutOff,
                &rlgCtx->lights[light].innerCutOff, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_LIGHT_OUTER_CUTOFF:
            rlgCtx->lights[light].outerCutOff = cosf(value*DEG2RAD);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].outerCutOff,
                &rlgCtx->lights[light].outerCutOff, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_LIGHT_ATTENUATION_CONSTANT:
            rlgCtx->lights[light].constant = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].constant, &value, SHADER_UNIFORM_FLOAT);

        case RLG_LIGHT_ATTENUATION_LINEAR:
            rlgCtx->lights[light].linear = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].linear, &value, SHADER_UNIFORM_FLOAT);

        case RLG_LIGHT_ATTENUATION_QUADRATIC:
            rlgCtx->lights[light].quadratic = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].quadratic, &value, SHADER_UNIFORM_FLOAT);
            break;

        default:
            break;
    }
}

void RLG_SetLightXYZ(unsigned int light, RLG_LightProperty property, float x, float y, float z)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightXYZ' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    Vector3 value = { x, y, z };

    switch (property)
    {
        case RLG_LIGHT_POSITION:
            rlgCtx->lights[light].position = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].position,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_DIRECTION:
            rlgCtx->lights[light].direction = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].direction,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_DIFFUSE:
            rlgCtx->lights[light].diffuse = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].diffuse,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_SPECULAR_TINT:
            rlgCtx->lights[light].specular = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].specular,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_ATTENUATION_CLQ:
            rlgCtx->lights[light].linear = y;
            rlgCtx->lights[light].constant = x;
            rlgCtx->lights[light].quadratic = z;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].linear, &y, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].constant, &x, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].quadratic, &z, SHADER_UNIFORM_FLOAT);
            break;

        default:
            break;
    }
}

void RLG_SetLightVec3(unsigned int light, RLG_LightProperty property, Vector3 value)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightVec3' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    switch (property)
    {
        case RLG_LIGHT_POSITION:
            rlgCtx->lights[light].position = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].position,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_DIRECTION:
            rlgCtx->lights[light].direction = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].direction,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_DIFFUSE:
            rlgCtx->lights[light].diffuse = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].diffuse,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_SPECULAR_TINT:
            rlgCtx->lights[light].specular = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].specular,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_ATTENUATION_CLQ:
            rlgCtx->lights[light].linear = value.y;
            rlgCtx->lights[light].constant = value.x;
            rlgCtx->lights[light].quadratic = value.z;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].linear, &value.y, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].constant, &value.x, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].quadratic, &value.z, SHADER_UNIFORM_FLOAT);
            break;

        default:
            break;
    }
}

void RLG_SetLightColor(unsigned int light, RLG_LightProperty property, Color color)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightColor' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    Vector3 value = {
        color.r/255.0f,
        color.g/255.0f,
        color.b/255.0f
    };

    switch (property)
    {
        case RLG_LIGHT_DIFFUSE:
            rlgCtx->lights[light].diffuse = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].diffuse,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_SPECULAR_TINT:
            rlgCtx->lights[light].specular = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].specular,
                &value, SHADER_UNIFORM_VEC3);
            break;

        default:
            break;
    }
}

float RLG_GetLightValue(unsigned int light, RLG_LightProperty property)
{
    float result = 0;

    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightValue' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return result;
    }

    switch (property)
    {
        case RLG_LIGHT_INNER_CUTOFF:
            result = acosf(rlgCtx->lights[light].innerCutOff)*RAD2DEG;    // REVIEW: Store in degrees in RAM?
            break;

        case RLG_LIGHT_OUTER_CUTOFF:
            result = acosf(rlgCtx->lights[light].outerCutOff)*RAD2DEG;    // REVIEW: Store in degrees in RAM?
            break;

        case RLG_LIGHT_ATTENUATION_CONSTANT:
            result = rlgCtx->lights[light].constant;
            break;

        case RLG_LIGHT_ATTENUATION_LINEAR:
            result = rlgCtx->lights[light].linear;
            break;

        case RLG_LIGHT_ATTENUATION_QUADRATIC:
            result = rlgCtx->lights[light].quadratic;
            break;

        default:
            break;
    }

    return result;
}

Vector3 RLG_GetLightVec3(unsigned int light, RLG_LightProperty property)
{
    Vector3 result = { 0 };

    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightVec3' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return result;
    }

    switch (property)
    {
        case RLG_LIGHT_POSITION:
            result = rlgCtx->lights[light].position;
            break;

        case RLG_LIGHT_DIRECTION:
            result = rlgCtx->lights[light].direction;
            break;

        case RLG_LIGHT_DIFFUSE:
            result = rlgCtx->lights[light].diffuse;
            break;

        case RLG_LIGHT_SPECULAR_TINT:
            result = rlgCtx->lights[light].specular;
            break;

        case RLG_LIGHT_ATTENUATION_CLQ:
            result.y = rlgCtx->lights[light].linear;
            result.x = rlgCtx->lights[light].constant;
            result.z = rlgCtx->lights[light].quadratic;
            break;

        default:
            break;
    }

    return result;
}

Color RLG_GetLightColor(unsigned int light, RLG_LightProperty property)
{
    Color result = BLACK;

    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightColor' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return result;
    }

    switch (property)
    {
        case RLG_LIGHT_DIFFUSE:
            result.r = 255*rlgCtx->lights[light].diffuse.x;
            result.g = 255*rlgCtx->lights[light].diffuse.y;
            result.b = 255*rlgCtx->lights[light].diffuse.z;
            break;

        case RLG_LIGHT_SPECULAR_TINT:
            result.r = 255*rlgCtx->lights[light].specular.x;
            result.g = 255*rlgCtx->lights[light].specular.y;
            result.b = 255*rlgCtx->lights[light].specular.z;
            break;

        default:
            break;
    }

    return result;
}

void RLG_LightTranslate(unsigned int light, float x, float y, float z)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightTranslate' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];
    l->position.x += x;
    l->position.y += y;
    l->position.z += z;

    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].position,
        &l->position, SHADER_UNIFORM_VEC3);
}

void RLG_LightTranslateV(unsigned int light, Vector3 v)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightTranslateV' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];
    l->position.x += v.x;
    l->position.y += v.y;
    l->position.z += v.z;

    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].position,
        &l->position, SHADER_UNIFORM_VEC3);
}

void RLG_LightRotateX(unsigned int light, float degrees)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotateX' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];
    float radians = DEG2RAD*degrees;
    float c = cosf(radians);
    float s = sinf(radians);

    l->direction.y = l->direction.y*c + l->direction.z*s;
    l->direction.z = -l->direction.y*s + l->direction.z*c;

    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].direction,
        &rlgCtx->lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_LightRotateY(unsigned int light, float degrees)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotateY' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];
    float radians = DEG2RAD*degrees;
    float c = cosf(radians);
    float s = sinf(radians);

    l->direction.x = l->direction.x*c - l->direction.z*s;
    l->direction.z = l->direction.x*s + l->direction.z*c;

    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].direction,
        &rlgCtx->lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_LightRotateZ(unsigned int light, float degrees)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotateZ' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];
    float radians = DEG2RAD*degrees;
    float c = cosf(radians);
    float s = sinf(radians);

    l->direction.x = l->direction.x*c + l->direction.y*s;
    l->direction.y = -l->direction.x*s + l->direction.y*c;

    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].direction,
        &rlgCtx->lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_LightRotate(unsigned int light, Vector3 axis, float degrees)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotate' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];
    float radians = -DEG2RAD*degrees;
    float halfTheta = radians*0.5f;

    float sinHalfTheta = sinf(halfTheta);
    Quaternion rotationQuat = {
        axis.x * sinHalfTheta,
        axis.y * sinHalfTheta,
        axis.z * sinHalfTheta,
        cosf(halfTheta)
    };

    // Convert the current direction vector to a quaternion
    Vector3 normalizedAxis = Vector3Normalize(axis);
    Quaternion directionQuat = {
        l->direction.x,
        l->direction.y,
        l->direction.z,
        0.0f
    };

    // Calculate the rotated direction quaternion
    Quaternion rotatedQuat = QuaternionMultiply(
        QuaternionMultiply(rotationQuat, directionQuat),
        QuaternionInvert(rotationQuat));

    // Update the light direction with the rotated direction
    l->direction = Vector3Normalize((Vector3){
        rotatedQuat.x, rotatedQuat.y, rotatedQuat.z
    });

    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].direction,
        &rlgCtx->lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_SetLightTarget(unsigned int light, float x, float y, float z)
{
    RLG_SetLightTargetV(light, (Vector3) { x, y, z });
}

void RLG_SetLightTargetV(unsigned int light, Vector3 targetPosition)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightTarget' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    rlgCtx->lights[light].direction = Vector3Normalize(Vector3Subtract(
        targetPosition, rlgCtx->lights[light].position));

    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].direction,
        &rlgCtx->lights[light].direction, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetLightTarget(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightTarget' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return (Vector3) { 0 };
    }

    return Vector3Add(
        rlgCtx->lights[light].position,
        rlgCtx->lights[light].direction);
}

void RLG_EnableShadow(unsigned int light, int shadowMapResolution)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_EnableShadow' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    if (l->type == RLG_OMNILIGHT)
    {
        TraceLog(LOG_WARNING, "The light [ID %i] is of type 'RLG_OMNILIGHT', shadow support for omnilights is not yet implemented, so please specify the light direction.", light, rlgCtx->lightCount);
    }

    if (l->shadowMap.width != shadowMapResolution)  ///< TODO: Review for CSM
    {
        if (l->shadowMap.id != 0)
        {
            rlUnloadTexture(l->shadowMap.depth.id);
            rlUnloadFramebuffer(l->shadowMap.id);
        }

        struct RLG_ShadowMap *sm = &l->shadowMap;

        sm->id = rlLoadFramebuffer(shadowMapResolution, shadowMapResolution);
        sm->width = sm->height = shadowMapResolution;
        rlEnableFramebuffer(sm->id);

        sm->depth.id = rlLoadTextureDepth(shadowMapResolution, shadowMapResolution, false);
        sm->depth.width = sm->depth.height = shadowMapResolution;
        sm->depth.format = 19, sm->depth.mipmaps = 1;

        rlTextureParameters(sm->depth.id, RL_TEXTURE_WRAP_S, RL_TEXTURE_WRAP_CLAMP);
        rlTextureParameters(sm->depth.id, RL_TEXTURE_WRAP_T, RL_TEXTURE_WRAP_CLAMP);
        rlFramebufferAttach(sm->id, sm->depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

        // REVIEW: Should this value be modifiable by the user?
        float texelSize = 1.0f/shadowMapResolution;
        SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].shadowMapTxlSz,
            &texelSize, SHADER_UNIFORM_FLOAT);

        // NOTE: This is a rough approximation, other factors may affect this variable.
        //       A better approach would be to calculate the bias in the shader,
        //       taking into account factors such as the distance between the
        //       light and the fragment position.
        l->depthBias = 0.1f*shadowMapResolution*tan(acosf(l->outerCutOff));
        SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].depthBias,
            &l->depthBias, SHADER_UNIFORM_FLOAT);
    }

    l->shadow = 1;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].shadow,
        &rlgCtx->lights[light].shadow, SHADER_UNIFORM_INT);
}

void RLG_DisableShadow(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_DisableShadow' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    rlgCtx->lights[light].shadow = 0;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].shadow,
        &rlgCtx->lights[light].shadow, SHADER_UNIFORM_INT);
}

bool RLG_IsShadowEnabled(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_IsShadowEnabled' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return false;
    }

    return rlgCtx->lights[light].shadow;
}

void RLG_SetShadowBias(unsigned int light, float value)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetShadowBias' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    rlgCtx->lights[light].depthBias = value;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locsLights[light].depthBias,
        &value, SHADER_UNIFORM_FLOAT);
}

float RLG_GetShadowBias(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetShadowBias' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return 0;
    }

    return rlgCtx->lights[light].depthBias;
}

// TODO: Review the operation for the CSM
void RLG_BeginShadowCast(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_BeginShadowCast' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    if (!l->shadow)
    {
        TraceLog(LOG_ERROR, "Light does not support shadow casting. Light ID: [%i]", light);
        return;
    }

    rlDrawRenderBatchActive();
    rlEnableFramebuffer(l->shadowMap.id);

    rlViewport(0, 0, l->shadowMap.width, l->shadowMap.height);

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();

#   define NEAR .01     // TODO: replace with rlGetCullDistanceNear()
#   define FAR 1000.    // TODO: replace with rlGetCullDistanceFar()

    // TODO: Review for CSM (aspect ratio ?)
    // NOTE: acos(outerCutoff) works only with spotlight
    double bound = NEAR*tan(acosf(l->outerCutOff));
    rlFrustum(-bound, bound, -bound, bound, NEAR, FAR);

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
//
    Matrix matView = MatrixLookAt(l->position, Vector3Add(l->position, l->direction), (Vector3){ 0, 1, 0 });
    rlMultMatrixf(MatrixToFloat(matView));
//
    rlEnableDepthTest();
    rlDisableColorBlend();
//
    Matrix viewProj = MatrixMultiply(matView, rlGetMatrixProjection());
    SetShaderValueMatrix(rlgCtx->lightShader, rlgCtx->locsLights[light].vpMatrix, viewProj);
//
}

void RLG_EndShadowCast(void)
{
    rlEnableColorBlend();

    rlDrawRenderBatchActive();
    rlDisableFramebuffer();

    rlViewport(0, 0, GetScreenWidth(), GetScreenHeight());

    rlMatrixMode(RL_PROJECTION);
    rlPopMatrix();

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
}

void RLG_ClearShadowMap(void)
{
    rlClearColor(255, 255, 255, 255);
    rlClearScreenBuffers();
}

void RLG_DrawShadowMap(unsigned int light, int x, int y, int w, int h)
{
    RLG_DrawShadowMapEx(light, x, y, w, h, 0.1f, 100.0f);
}

void RLG_DrawShadowMapEx(unsigned int light, int x, int y, int w, int h, float near, float far)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_DrawShadowMap' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    if (near != rlgCtx->shadowMapShaderData.near)
    {
        rlgCtx->shadowMapShaderData.near = near;
        SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->shadowMapShaderData.locNear,
            &rlgCtx->shadowMapShaderData.near, SHADER_UNIFORM_FLOAT);
    }

    if (far != rlgCtx->shadowMapShaderData.far)
    {
        rlgCtx->shadowMapShaderData.far = far;
        SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->shadowMapShaderData.locFar,
            &rlgCtx->shadowMapShaderData.far, SHADER_UNIFORM_FLOAT);
    }

    BeginShaderMode(rlgCtx->shadowMapShader);
    rlBegin(RL_QUADS);

        rlSetTexture(rlgCtx->lights[light].shadowMap.depth.id);

        rlTexCoord2f(0, 0); rlVertex2i(x, y);
        rlTexCoord2f(0, 1); rlVertex2i(x, y + h);
        rlTexCoord2f(1, 1); rlVertex2i(x + w, y + h);
        rlTexCoord2f(1, 0); rlVertex2i(x + w, y);

        rlSetTexture(rlGetTextureIdDefault());

    rlEnd();
    EndShaderMode();
}

void RLG_CastMesh(Mesh mesh, Matrix transform)
{
    // Bind shader program
    rlEnableShader(rlgCtx->depthShader.id);

    // Get a copy of current matrices to work with,
    // just in case stereo render is required, and we need to modify them
    // NOTE: At this point the modelview matrix just contains the view matrix (camera)
    // That's because BeginMode3D() sets it and there is no model-drawing function
    // that modifies it, all use rlPushMatrix() and rlPopMatrix()
    Matrix matModel = MatrixIdentity();
    Matrix matView = rlGetMatrixModelview();
    Matrix matModelView = MatrixIdentity();
    Matrix matProjection = rlGetMatrixProjection();

    // Accumulate several model transformations:
    //    transform: model transformation provided (includes DrawModel() params combined with model.transform)
    //    rlGetMatrixTransform(): rlgl internal transform matrix due to push/pop matrix stack
    matModel = MatrixMultiply(transform, rlGetMatrixTransform());

    // Get model-view matrix
    matModelView = MatrixMultiply(matModel, matView);

    // Try binding vertex array objects (VAO) or use VBOs if not possible
    if (!rlEnableVertexArray(mesh.vaoId))
    {
        // Bind mesh VBO data: vertex position (shader-location = 0)
        rlEnableVertexBuffer(mesh.vboId[0]);
        rlSetVertexAttribute(rlgCtx->depthShader.locs[SHADER_LOC_VERTEX_POSITION], 3, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(rlgCtx->depthShader.locs[SHADER_LOC_VERTEX_POSITION]);

        // If vertex indices exist, bine the VBO containing the indices
        if (mesh.indices != NULL) rlEnableVertexBufferElement(mesh.vboId[6]);
    }

    int eyeCount = rlIsStereoRenderEnabled() ? 2 : 1;

    for (int eye = 0; eye < eyeCount; eye++)
    {
        // Calculate model-view-projection matrix (MVP)
        Matrix matModelViewProjection = MatrixIdentity();
        if (eyeCount == 1) matModelViewProjection = MatrixMultiply(matModelView, matProjection);
        else
        {
            // Setup current eye viewport (half screen width)
            rlViewport(eye*rlGetFramebufferWidth()/2, 0, rlGetFramebufferWidth()/2, rlGetFramebufferHeight());
            matModelViewProjection = MatrixMultiply(MatrixMultiply(matModelView, rlGetMatrixViewOffsetStereo(eye)), rlGetMatrixProjectionStereo(eye));
        }

        // Send combined model-view-projection matrix to shader
        rlSetUniformMatrix(rlgCtx->depthShader.locs[SHADER_LOC_MATRIX_MVP], matModelViewProjection);

        // Draw mesh
        if (mesh.indices != NULL) rlDrawVertexArrayElements(0, mesh.triangleCount*3, 0);
        else rlDrawVertexArray(0, mesh.vertexCount);
    }

    // Disable all possible vertex array objects (or VBOs)
    rlDisableVertexArray();
    rlDisableVertexBuffer();
    rlDisableVertexBufferElement();

    // Disable shader program
    rlDisableShader();

    // Restore rlgl internal modelview and projection matrices
    rlSetMatrixModelview(matView);
    rlSetMatrixProjection(matProjection);
}

void RLG_CastModel(Model model, Vector3 position, float scale)
{
    Vector3 vScale = { scale, scale, scale };
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RLG_CastModelEx(model, position, rotationAxis, 0.0f, vScale);
}

void RLG_CastModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale)
{
    Matrix matScale = MatrixScale(scale.x, scale.y, scale.z);
    Matrix matRotation = MatrixRotate(rotationAxis, rotationAngle*DEG2RAD);
    Matrix matTranslation = MatrixTranslate(position.x, position.y, position.z);

    Matrix matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
    model.transform = MatrixMultiply(model.transform, matTransform);

    for (int i = 0; i < model.meshCount; i++)
    {
        RLG_CastMesh(model.meshes[i], model.transform);
    }
}

void RLG_DrawMesh(Mesh mesh, Material material, Matrix transform)
{
    // Bind shader program
    rlEnableShader(rlgCtx->lightShader.id);

    // Send required data to shader (matrices, values)
    //-----------------------------------------------------
    // Upload to shader globalLight.colDiffuse
    if (rlgCtx->lightShader.locs[SHADER_LOC_COLOR_DIFFUSE] != -1)
    {
        float values[4] = {
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.r/255.0f,
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.g/255.0f,
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.b/255.0f,
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.a/255.0f
        };

        rlSetUniform(rlgCtx->lightShader.locs[SHADER_LOC_COLOR_DIFFUSE], values, SHADER_UNIFORM_VEC4, 1);
    }

    // Upload to shader globalLight.colSpecular (if location available)
    if (rlgCtx->lightShader.locs[SHADER_LOC_COLOR_SPECULAR] != -1)
    {
        float values[4] = {
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.r/255.0f,
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.g/255.0f,
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.b/255.0f,
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.a/255.0f
        };

        rlSetUniform(rlgCtx->lightShader.locs[SHADER_LOC_COLOR_SPECULAR], values, SHADER_UNIFORM_VEC4, 1);
    }

    // Get a copy of current matrices to work with,
    // just in case stereo render is required, and we need to modify them
    // NOTE: At this point the modelview matrix just contains the view matrix (camera)
    // That's because BeginMode3D() sets it and there is no model-drawing function
    // that modifies it, all use rlPushMatrix() and rlPopMatrix()
    Matrix matModel = MatrixIdentity();
    Matrix matView = rlGetMatrixModelview();
    Matrix matModelView = MatrixIdentity();
    Matrix matProjection = rlGetMatrixProjection();

    // Upload view and projection matrices (if locations available)
    if (rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_VIEW] != -1) rlSetUniformMatrix(rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_VIEW], matView);
    if (rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_PROJECTION] != -1) rlSetUniformMatrix(rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_PROJECTION], matProjection);

    // Model transformation matrix is sent to shader uniform location: SHADER_LOC_MATRIX_MODEL
    if (rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_MODEL] != -1) rlSetUniformMatrix(rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_MODEL], transform);

    // Accumulate several model transformations:
    //    transform: model transformation provided (includes DrawModel() params combined with model.transform)
    //    rlGetMatrixTransform(): rlgl internal transform matrix due to push/pop matrix stack
    matModel = MatrixMultiply(transform, rlGetMatrixTransform());

    // Get model-view matrix
    matModelView = MatrixMultiply(matModel, matView);

    // Upload model normal matrix (if locations available)
    if (rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_NORMAL] != -1) rlSetUniformMatrix(rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_NORMAL], MatrixTranspose(MatrixInvert(matModel)));
    //-----------------------------------------------------

    // Bind active texture maps (if available)
    for (int i = 0; i < 11; i++)
    {
        if (material.maps[i].texture.id > 0)
        {
            // Select current shader texture slot
            rlActiveTextureSlot(i);

            // Enable texture for active slot
            if ((i == MATERIAL_MAP_IRRADIANCE) || (i == MATERIAL_MAP_PREFILTER) || (i == MATERIAL_MAP_CUBEMAP))
                rlEnableTextureCubemap(material.maps[i].texture.id);
            else rlEnableTexture(material.maps[i].texture.id);

            rlSetUniform(rlgCtx->lightShader.locs[SHADER_LOC_MAP_DIFFUSE + i], &i, SHADER_UNIFORM_INT, 1);
        }
    }

    // Bind depth textures for shadow mapping
    for (int i = 0; i < rlgCtx->lightCount; i++)
    {
        if (rlgCtx->lights[i].shadow)
        {
            int j = 11 + i;
            rlActiveTextureSlot(j);
            rlEnableTexture(rlgCtx->lights[i].shadowMap.depth.id);
            rlSetUniform(rlgCtx->locsLights[i].shadowMap, &j, SHADER_UNIFORM_INT, 1);
        }
    }

    // Try binding vertex array objects (VAO) or use VBOs if not possible
    // WARNING: UploadMesh() enables all vertex attributes available in mesh and sets default attribute values
    // for shader expected vertex attributes that are not provided by the mesh (i.e. colors)
    // This could be a dangerous approach because different meshes with different shaders can enable/disable some attributes
    if (!rlEnableVertexArray(mesh.vaoId))
    {
        // Bind mesh VBO data: vertex position (shader-location = 0)
        rlEnableVertexBuffer(mesh.vboId[0]);
        rlSetVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_POSITION], 3, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_POSITION]);

        // Bind mesh VBO data: vertex texcoords (shader-location = 1)
        rlEnableVertexBuffer(mesh.vboId[1]);
        rlSetVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD01], 2, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD01]);

        if (rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_NORMAL] != -1)
        {
            // Bind mesh VBO data: vertex normals (shader-location = 2)
            rlEnableVertexBuffer(mesh.vboId[2]);
            rlSetVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_NORMAL], 3, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_NORMAL]);
        }

        // Bind mesh VBO data: vertex colors (shader-location = 3, if available)
        if (rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_COLOR] != -1)
        {
            if (mesh.vboId[3] != 0)
            {
                rlEnableVertexBuffer(mesh.vboId[3]);
                rlSetVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_COLOR], 4, RL_UNSIGNED_BYTE, 1, 0, 0);
                rlEnableVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_COLOR]);
            }
            else
            {
                // Set default value for defined vertex attribute in shader but not provided by mesh
                // WARNING: It could result in GPU undefined behaviour
                float value[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
                rlSetVertexAttributeDefault(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_COLOR], value, SHADER_ATTRIB_VEC4, 4);
                rlDisableVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_COLOR]);
            }
        }

        // Bind mesh VBO data: vertex tangents (shader-location = 4, if available)
        if (rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TANGENT] != -1)
        {
            rlEnableVertexBuffer(mesh.vboId[4]);
            rlSetVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TANGENT], 4, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TANGENT]);
        }

        // Bind mesh VBO data: vertex texcoords2 (shader-location = 5, if available)
        if (rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD02] != -1)
        {
            rlEnableVertexBuffer(mesh.vboId[5]);
            rlSetVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD02], 2, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(rlgCtx->lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD02]);
        }

        if (mesh.indices != NULL) rlEnableVertexBufferElement(mesh.vboId[6]);
    }

    int eyeCount = 1;
    if (rlIsStereoRenderEnabled()) eyeCount = 2;

    for (int eye = 0; eye < eyeCount; eye++)
    {
        // Calculate model-view-projection matrix (MVP)
        Matrix matModelViewProjection = MatrixIdentity();
        if (eyeCount == 1) matModelViewProjection = MatrixMultiply(matModelView, matProjection);
        else
        {
            // Setup current eye viewport (half screen width)
            rlViewport(eye*rlGetFramebufferWidth()/2, 0, rlGetFramebufferWidth()/2, rlGetFramebufferHeight());
            matModelViewProjection = MatrixMultiply(MatrixMultiply(matModelView, rlGetMatrixViewOffsetStereo(eye)), rlGetMatrixProjectionStereo(eye));
        }

        // Send combined model-view-projection matrix to shader
        rlSetUniformMatrix(rlgCtx->lightShader.locs[SHADER_LOC_MATRIX_MVP], matModelViewProjection);

        // Draw mesh
        if (mesh.indices != NULL) rlDrawVertexArrayElements(0, mesh.triangleCount*3, 0);
        else rlDrawVertexArray(0, mesh.vertexCount);
    }

    // Unbind all bound texture maps
    for (int i = 0; i < 11; i++)
    {
        if (material.maps[i].texture.id > 0)
        {
            // Select current shader texture slot
            rlActiveTextureSlot(i);

            // Disable texture for active slot
            if ((i == MATERIAL_MAP_IRRADIANCE) ||
                (i == MATERIAL_MAP_PREFILTER) ||
                (i == MATERIAL_MAP_CUBEMAP)) rlDisableTextureCubemap();
            else rlDisableTexture();
        }
    }

    // Unbind depth textures
    for (int i = 0; i < rlgCtx->lightCount; i++)
    {
        if (rlgCtx->lights[i].shadow)
        {
            rlActiveTextureSlot(11 + i);
            rlDisableTexture();
        }
    }

    // Disable all possible vertex array objects (or VBOs)
    rlDisableVertexArray();
    rlDisableVertexBuffer();
    rlDisableVertexBufferElement();

    // Disable shader program
    rlDisableShader();

    // Restore rlgl internal modelview and projection matrices
    rlSetMatrixModelview(matView);
    rlSetMatrixProjection(matProjection);
}

void RLG_DrawModel(Model model, Vector3 position, float scale, Color tint)
{
    Vector3 vScale = { scale, scale, scale };
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RLG_DrawModelEx(model, position, rotationAxis, 0.0f, vScale, tint);
}

void RLG_DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
{
    Matrix matScale = MatrixScale(scale.x, scale.y, scale.z);
    Matrix matRotation = MatrixRotate(rotationAxis, rotationAngle*DEG2RAD);
    Matrix matTranslation = MatrixTranslate(position.x, position.y, position.z);

    Matrix matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
    model.transform = MatrixMultiply(model.transform, matTransform);

    for (int i = 0; i < model.meshCount; i++)
    {
        Color color = model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color;

        Color colorTint = WHITE;
        colorTint.r = (unsigned char)((color.r*tint.r)/255);
        colorTint.g = (unsigned char)((color.g*tint.g)/255);
        colorTint.b = (unsigned char)((color.b*tint.b)/255);
        colorTint.a = (unsigned char)((color.a*tint.a)/255);

        model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color = colorTint;
        RLG_DrawMesh(model.meshes[i], model.materials[model.meshMaterial[i]], model.transform);
        model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color = color;
    }
}

#endif //RLIGHTS_IMPLEMENTATION
#endif //RLIGHTS_H