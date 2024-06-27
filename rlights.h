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
    RLG_MAP_METALNESS,                  ///< Metalness map used to define the metallic property of the material.
    RLG_MAP_ROUGHNESS,                  ///< Roughness map used to define the surface roughness of the material.
    RLG_MAP_OCCLUSION,                  ///< Occlusion map used to define ambient occlusion, affecting the shading of the material.
    RLG_MAP_EMISSIVE,                   ///< Emissive map used for emitting light.
    RLG_MAP_NORMAL,                     ///< Normal map used for bump mapping.
    RLG_MAP_HEIGHT                      ///< Height map used for parallax mapping.
} RLG_MaterialMap;

/**
 * @brief Enum representing different material properties.
 */
typedef enum {
    RLG_MAT_EMISSIVE_TINT,              ///< Emissive tint property of the material.
    RLG_MAT_AMBIENT_TINT,               ///< Ambient tint property of the material.
    RLG_MAT_METALNESS,                  ///< Metalness property defining the metallic nature of the material.
    RLG_MAT_ROUGHNESS,                  ///< Roughness property defining the surface roughness of the material.
    RLG_MAT_SPECULAR,                   ///< Specular property defining the specular reflection of the material.
    RLG_MAT_HEIGHT_SCALE,               ///< Height scale property for adjusting the intensity of parallax mapping.
    RLG_MAT_HEIGHT_MIN_LAYERS,          ///< Minimum layers property for parallax mapping (if < 1 deep parallax is disabled).
    RLG_MAT_HEIGHT_MAX_LAYERS           ///< Maximum layers property for parallax mapping (if < 2 deep parallax is disabled).
} RLG_MaterialProperty;

/**
 * @brief Enum representing different properties of a light.
 */
typedef enum {
    RLG_LIGHT_POSITION,                 ///< Position of the light.
    RLG_LIGHT_DIRECTION,                ///< Direction of the light.
    RLG_LIGHT_COLOR,                    ///< Diffuse color of the light.
    RLG_LIGHT_ENERGY,                   ///< Energy factor of the light.
    RLG_LIGHT_SPECULAR,                 ///< Specular tint color of the light.
    RLG_LIGHT_SIZE,                     ///< Light size, affects fade and shadow blur (spotlight, omnilight only).
    RLG_LIGHT_INNER_CUTOFF,             ///< Inner cutoff angle of a spotlight.
    RLG_LIGHT_OUTER_CUTOFF,             ///< Outer cutoff angle of a spotlight.
    RLG_LIGHT_ATTENUATION_CLQ,          ///< Attenuation coefficients (constant, linear, quadratic) of the light.
    RLG_LIGHT_ATTENUATION_CONSTANT,     ///< Constant attenuation coefficient of the light.
    RLG_LIGHT_ATTENUATION_LINEAR,       ///< Linear attenuation coefficient of the light.
    RLG_LIGHT_ATTENUATION_QUADRATIC     ///< Quadratic attenuation coefficient of the light.
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
 * @brief Set a color value for a specific light.
 * 
 * @param light The index of the light to modify.
 * @param color The color to assign to the light.
 */
void RLG_SetLightColor(unsigned int light, Color color);

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
 * @brief Get the color value of a specific light.
 * 
 * @param light The index of the light to retrieve the value from.
 * @return The color value of the specified light.
 */
Color RLG_GetLightColor(unsigned int light);

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

    "#define PI 3.1415926535897932384626433832795028\n"

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
        "vec3 color;"               ///< Diffuse color of the light
        "float energy;"             ///< Energy factor of the diffuse light color
        "float specular;"           ///< Specular amount of the light
        "float size;"               ///< Light size (spotlight, omnilight only)
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

    "uniform lowp int useMetalnessMap;"
    "uniform lowp int useRoughnessMap;"
    "uniform lowp int useOcclusionMap;"
    "uniform lowp int useEmissiveMap;"
    "uniform lowp int useNormalMap;"
    "uniform lowp int useHeightMap;"

    "uniform sampler2D texture0;"   // albedo
    "uniform sampler2D texture1;"   // metalness
    "uniform sampler2D texture2;"   // normal
    "uniform sampler2D texture3;"   // roughness
    "uniform sampler2D texture4;"   // occlusion
    "uniform sampler2D texture5;"   // emissive
    "uniform sampler2D texture6;"   // height

    "uniform vec3 colEmissive;"     // sent by rlights
    "uniform vec4 colDiffuse;"      // sent by raylib
    "uniform vec3 colAmbient;"      // sent by rlights

    "uniform float metalness;"
    "uniform float roughness;"
    "uniform float specular;"

    "uniform float heightScale;"
    "uniform lowp int parallaxMinLayers;"
    "uniform lowp int parallaxMaxLayers;"

    "uniform vec3 viewPos;"

    "float DistributionGGX(float cosTheta, float alpha)"
    "{"
        "float a = cosTheta*alpha;"
        "float k = alpha/(1.0 - cosTheta*cosTheta + a*a);"
        "return k*k*(1.0/PI);"
    "}"

    // From Earl Hammon, Jr. "PBR Diffuse Lighting for GGX+Smith Microsurfaces"
    // SEE: https://www.gdcvault.com/play/1024478/PBR-Diffuse-Lighting-for-GGX
    "float GeometrySmith(float NdotL, float NdotV, float alpha)"
    "{"
        "return 0.5/mix(2.0*NdotL*NdotV, NdotL + NdotV, alpha);"
    "}"

    "float SchlickFresnel(float u)"
    "{"
        "float m = 1.0 - u;"
        "float m2 = m*m;"
        "return m2*m2*m;" // pow(m,5)
    "}"

    "vec3 ComputeF0(float metallic, float specular, vec3 albedo)"
    "{"
        "float dielectric = 0.16*specular*specular;"
        // use albedo*metallic as colored specular reflectance at 0 angle for metallic materials
        // SEE: https://google.github.io/filament/Filament.md.html
        "return mix(vec3(dielectric), albedo, vec3(metallic));"
    "}"

    "vec2 Parallax(vec2 uv, vec3 V)"
    "{"
        "float height = 1.0 - TEX(texture6, uv).r;"
        "return uv - vec2(V.xy/V.z)*height*heightScale;"
    "}"

    "vec2 DeepParallax(vec2 uv, vec3 V)"
    "{"
        "float numLayers = mix("
            "float(parallaxMaxLayers),"
            "float(parallaxMinLayers),"
            "abs(dot(vec3(0.0, 0.0, 1.0), V)));"

        "float layerDepth = 1.0/numLayers;"
        "float currentLayerDepth = 0.0;"

        "vec2 P = V.xy/V.z*heightScale;"
        "vec2 deltaTexCoord = P/numLayers;"
    
        "vec2 currentUV = uv;"
        "float currentDepthMapValue = 1.0 - TEX(texture6, currentUV).y;"
        
        "while(currentLayerDepth < currentDepthMapValue)"
        "{"
            "currentUV += deltaTexCoord;"
            "currentLayerDepth += layerDepth;"
            "currentDepthMapValue = 1.0 - TEX(texture6, currentUV).y;"
        "}"

        "vec2 prevTexCoord = currentUV - deltaTexCoord;"
        "float afterDepth  = currentDepthMapValue + currentLayerDepth;"
        "float beforeDepth = 1.0 - TEX(texture6, prevTexCoord).y - currentLayerDepth - layerDepth;"

        "float weight = afterDepth/(afterDepth - beforeDepth);"
        "return prevTexCoord*weight + currentUV*(1.0 - weight);"
    "}"

    "float Shadow(int i)"
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
                "float pcfDepth = TEX(lights[i].shadowMap, projCoords.xy + vec2(x, y)*lights[i].shadowMapTxlSz).r;"
                "shadow += step(depth, pcfDepth);"
            "}"
        "}"

        "return shadow/9.0;"
    "}"

    "void main()"
    "{"
        // Compute the view direction vector for this fragment
        "vec3 V = normalize(viewPos - fragPosition);"

        // Compute fragTexCoord (UV), apply parallax if height map is enabled
        "vec2 uv = fragTexCoord;"
        "if (useHeightMap != 0)"
        "{"
            "uv = (parallaxMinLayers > 0 && parallaxMaxLayers > 1)"
                "? DeepParallax(uv, V) : Parallax(uv, V);"

            "if (uv.x < 0.0 || uv.y < 0.0 || uv.x > 1.0 || uv.y > 1.0)"
            "{"
                "discard;"
            "}"
        "}"

        // Compute albedo (base color) by sampling the texture and multiplying by the diffuse color
        "vec3 albedo = TEX(texture0, uv).rgb;"
        "albedo *= colDiffuse.rgb*fragColor.rgb;"

        // Compute metallic factor; if a metalness map is used, sample it
        "float metallic = metalness;"
        "if (useMetalnessMap != 0) metallic *= TEX(texture1, uv).b;"

        // Compute roughness factor; if a roughness map is used, sample it
        "float rough = roughness;"
        "if (useRoughnessMap != 0) rough *= TEX(texture3, uv).g;"

        // Compute F0 (reflectance at normal incidence) based on the metallic factor
        "vec3 F0 = ComputeF0(metallic, specular, albedo);"

        // Compute the normal vector; if a normal map is used, transform it to tangent space
        "vec3 N = (useNormalMap == 0) ? normalize(fragNormal)"
            ": normalize(TBN*(TEX(texture2, uv).rgb*2.0 - 1.0));"

        // Compute the dot product of the normal and view direction
        "float NdotV = dot(N, V);"
        "float cNdotV = max(NdotV, 1e-4);"  // Clamped to avoid division by zero

        // Initialize diffuse and specular lighting accumulators
        "vec3 diffLighting = vec3(0.0);"
        "vec3 specLighting = vec3(0.0);"

        // Loop through all lights
        "for (int i = 0; i < NUM_LIGHTS; i++)"
        "{"
            "if (lights[i].enabled != 0)"
            "{"
                "float size_A = 0.0;"
                "vec3 L = vec3(0.0);"

                // Compute the light direction vector
                "if (lights[i].type != DIRLIGHT)"
                "{"
                    "vec3 LV = lights[i].position - fragPosition;"
                    "L = normalize(LV);"

                    // If the light has a size, compute the attenuation factor based on the distance
                    "if (lights[i].size > 0.0)"
                    "{"
                        "float t = lights[i].size/max(0.001, length(LV));"
                        "size_A = max(0.0, 1.0 - 1.0/sqrt(1.0 + t*t));"
                    "}"
                "}"
                "else"
                "{"
                    // For directional lights, use the negative direction as the light direction
                    "L = normalize(-lights[i].direction);"
                "}"

                // Compute the dot product of the normal and light direction, adjusted by size_A
                "float NdotL = min(size_A + dot(N, L), 1.0);"
                "float cNdotL = max(NdotL, 0.0);" // clamped NdotL

                // Compute the halfway vector between the view and light directions
                "vec3 H = normalize(V + L);"
                "float cNdotH = clamp(size_A + dot(N, H), 0.0, 1.0);"
                "float cLdotH = clamp(size_A + dot(L, H), 0.0, 1.0);"

                // Compute light color energy
                "vec3 lightColE = lights[i].color*lights[i].energy;"

                // Compute diffuse lighting (Burley model) if the material is not fully metallic
                "vec3 diffLight = vec3(0.0);"
                "if (metallic < 1.0)"
                "{"
                    "float FD90_minus_1 = 2.0*cLdotH*cLdotH*rough - 0.5;"
                    "float FdV = 1.0 + FD90_minus_1*SchlickFresnel(cNdotV);"
                    "float FdL = 1.0 + FD90_minus_1*SchlickFresnel(cNdotL);"

                    "float diffBRDF = (1.0/PI)*FdV*FdL*cNdotL;"
                    "diffLight = diffBRDF*lightColE;"
                "}"

                // Compute specular lighting using the Schlick-GGX model
                // NOTE: When roughness is 0, specular light should not be entirely disabled.
                // TODO: Handle perfect mirror reflection when roughness is 0.
                "vec3 specLight = vec3(0.0);"
                "if (rough > 0.0)"
                "{"
                    "float alphaGGX = rough*rough;"
                    "float D = DistributionGGX(cNdotH, alphaGGX);"
                    "float G = GeometrySmith(cNdotL, cNdotV, alphaGGX);"

                    "float cLdotH5 = SchlickFresnel(cLdotH);"
                    "float F90 = clamp(50.0*F0.g, 0.0, 1.0);"
                    "vec3 F = F0 + (F90 - F0)*cLdotH5;"

                    "vec3 specBRDF = cNdotL*D*F*G;"
                    "specLight = specBRDF*lightColE*lights[i].specular;"
                "}"

                // Apply spotlight effect if the light is a spotlight
                "float intensity = 1.0;"
                "if (lights[i].type == SPOTLIGHT)"
                "{"
                    "float theta = dot(L, normalize(-lights[i].direction));"
                    "float epsilon = (lights[i].innerCutOff - lights[i].outerCutOff);"
                    "intensity = smoothstep(0.0, 1.0, (theta - lights[i].outerCutOff)/epsilon);"
                "}"

                // Apply attenuation based on the distance from the light
                "float distance    = length(lights[i].position - fragPosition);"
                "float attenuation = 1.0/(lights[i].constant +"
                                         "lights[i].linear*distance +"
                                         "lights[i].quadratic*(distance*distance));"

                // Apply shadow factor if the light casts shadows
                "float shadow = (lights[i].shadow != 0) ? Shadow(i) : 1.0;"

                // Compute the final intensity factor combining intensity, attenuation, and shadow
                "float factor = intensity*attenuation*shadow;"

                // Accumulate the diffuse and specular lighting contributions
                "diffLighting += diffLight*factor;"
                "specLighting += specLight*factor;"
            "}"
        "}"

        // Compute ambient (with occlusion)
        "vec3 ambient = colAmbient;"
        "if (useOcclusionMap != 0)"
        "{"
            "float ao = TEX(texture4, uv).r;"
            "ambient *= ao;"
        "}"

        // Compute the final diffuse color, including ambient and diffuse lighting contributions
        "vec3 diffuse = albedo*(ambient + diffLighting);"

        // Compute emission color; if an emissive map is used, sample it
        "vec3 emission = colEmissive;"
        "if (useEmissiveMap != 0)"
        "{"
            "emission *= TEX(texture5, uv).rgb;"
        "}"

        // Compute the final fragment color by combining diffuse, specular, and emission contributions
        GLSL_FINAL_COLOR("vec4(diffuse + specLighting + emission, 1.0)")
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

struct RLG_ShadowMap
{
    Texture2D depth;
    unsigned int id;
    int width, height;
};

struct RLG_Material
{
    struct RLG_MaterialLocs
    {
        int colEmissive;
        int colAmbient;

        int metalness;
        int roughness;
        int specular;

        int heightScale;
        int parallaxMinLayers;
        int parallaxMaxLayers;

        int useMetalnessMap;
        int useRoughnessMap;
        int useOcclusionMap;
        int useEmissiveMap;
        int useNormalMap;
        int useHeightMap;
    }
    locs;

    struct RLG_MaterialData
    {
        Vector3 colEmissive;
        Vector3 colAmbient;

        float metalness;
        float roughness;
        float specular;

        float heightScale;
        int parallaxMinLayers;
        int parallaxMaxLayers;

        int useMetalnessMap;
        int useRoughnessMap;
        int useOcclusionMap;
        int useEmissiveMap;
        int useNormalMap;
        int useHeightMap;
    }
    data;
};

struct RLG_Light
{
    struct RLG_LightLocs
    {
        int vpMatrix;       ///< NOTE: Not present in the Light shader struct but in a separate uniform
        int shadowMap;
        int position;
        int direction;
        int color;
        int energy;
        int specular;
        int size;
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
    }
    locs;

    struct RLG_LightData
    {
        struct RLG_ShadowMap shadowMap;
        Vector3 position;
        Vector3 direction;
        Vector3 color;
        float energy;
        float specular;
        float size;
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
    }
    data;
};

static struct RLG_Core
{
    /* Lighting shader data*/

    struct RLG_Material material;
    struct RLG_Light *lights;
    int lightCount;

    Vector3 viewPos;
    int locViewPos;

    /* Shadow map rendeering shader data */

    float depthNear;
    float depthFar;

    int locDepthNear;
    int locDepthFar;

    /* Shaders */

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

    // Get global lighting shader locations (and init viewPos vector)
    rlgCtx->locViewPos = GetShaderLocation(rlgCtx->lightShader, "viewPos");
    rlgCtx->viewPos = (Vector3) { 0 };

    // Initialize material struct with zeroes
    rlgCtx->material = (struct RLG_Material) { 0 };

    // Retrieving global shader locations
    rlgCtx->material.locs.parallaxMinLayers = GetShaderLocation(rlgCtx->lightShader, "parallaxMinLayers");
    rlgCtx->material.locs.parallaxMaxLayers = GetShaderLocation(rlgCtx->lightShader, "parallaxMaxLayers");
    rlgCtx->material.locs.useMetalnessMap = GetShaderLocation(rlgCtx->lightShader, "useMetalnessMap");
    rlgCtx->material.locs.useRoughnessMap = GetShaderLocation(rlgCtx->lightShader, "useRoughnessMap");
    rlgCtx->material.locs.useOcclusionMap = GetShaderLocation(rlgCtx->lightShader, "useOcclusionMap");
    rlgCtx->material.locs.useEmissiveMap = GetShaderLocation(rlgCtx->lightShader, "useEmissiveMap");
    rlgCtx->material.locs.useNormalMap = GetShaderLocation(rlgCtx->lightShader, "useNormalMap");
    rlgCtx->material.locs.useHeightMap = GetShaderLocation(rlgCtx->lightShader, "useHeightMap");
    rlgCtx->material.locs.heightScale = GetShaderLocation(rlgCtx->lightShader, "heightScale");
    rlgCtx->material.locs.colEmissive = GetShaderLocation(rlgCtx->lightShader, "colEmissive");
    rlgCtx->material.locs.colAmbient = GetShaderLocation(rlgCtx->lightShader, "colAmbient");
    rlgCtx->material.locs.metalness = GetShaderLocation(rlgCtx->lightShader, "metalness");
    rlgCtx->material.locs.roughness = GetShaderLocation(rlgCtx->lightShader, "roughness");
    rlgCtx->material.locs.specular = GetShaderLocation(rlgCtx->lightShader, "specular");

    // Define default global uniforms (define only no zero by default)
    rlgCtx->material.data.colAmbient = (Vector3) { 0.1f, 0.1f, 0.1f };
    rlgCtx->material.data.heightScale = 0.05f;
    rlgCtx->material.data.roughness = 1.0f;
    rlgCtx->material.data.specular = 1.0f;

    // Send default globals uniforms (no need to send zero-values)
    SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.heightScale, &rlgCtx->material.data.heightScale, SHADER_UNIFORM_FLOAT);
    SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.colAmbient, &rlgCtx->material.data.colAmbient, SHADER_UNIFORM_VEC3);
    SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.roughness, &rlgCtx->material.data.roughness, SHADER_UNIFORM_FLOAT);
    SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.specular, &rlgCtx->material.data.specular, SHADER_UNIFORM_FLOAT);

    // Allocation and initialization of the desired number of lights
    rlgCtx->lights = (struct RLG_Light*)calloc(count, sizeof(struct RLG_Light));
    for (int i = 0; i < count; i++)
    {
        struct RLG_Light *light = &rlgCtx->lights[i];

        light->data.shadowMap      = (struct RLG_ShadowMap) { 0 };
        light->data.position       = (Vector3) { 0 };
        light->data.direction      = (Vector3) { 0 };
        light->data.color          = (Vector3) { 1.0f, 1.0f, 1.0f };
        light->data.energy         = 1.0f;
        light->data.specular       = 1.0f;
        light->data.size           = 0.0f;
        light->data.innerCutOff    = -1.0f;
        light->data.outerCutOff    = -1.0f;
        light->data.constant       = 1.0f;
        light->data.linear         = 0.0f;
        light->data.quadratic      = 0.0f;
        light->data.shadowMapTxlSz = 0.0f;
        light->data.depthBias      = 0.0f;
        light->data.type           = RLG_DIRECTIONAL;
        light->data.shadow         = 0;
        light->data.enabled        = 0;

        light->locs.vpMatrix       = GetShaderLocation(rlgCtx->lightShader, TextFormat("matLights[%i]", i));
        light->locs.shadowMap      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].shadowMap", i));
        light->locs.position       = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].position", i));
        light->locs.direction      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].direction", i));
        light->locs.color          = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].color", i));
        light->locs.energy         = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].energy", i));
        light->locs.specular       = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].specular", i));
        light->locs.size           = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].size", i));
        light->locs.innerCutOff    = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].innerCutOff", i));
        light->locs.outerCutOff    = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].outerCutOff", i));
        light->locs.constant       = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].constant", i));
        light->locs.linear         = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].linear", i));
        light->locs.quadratic      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].quadratic", i));
        light->locs.shadowMapTxlSz = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].shadowMapTxlSz", i));
        light->locs.depthBias      = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].depthBias", i));
        light->locs.type           = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].type", i));
        light->locs.shadow         = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].shadow", i));
        light->locs.enabled        = GetShaderLocation(rlgCtx->lightShader, TextFormat("lights[%i].enabled", i));

        SetShaderValue(rlgCtx->lightShader, light->locs.color, &light->data.color, SHADER_UNIFORM_VEC3);
        SetShaderValue(rlgCtx->lightShader, light->locs.energy, &light->data.energy, SHADER_UNIFORM_FLOAT);
        SetShaderValue(rlgCtx->lightShader, light->locs.specular, &light->data.specular, SHADER_UNIFORM_FLOAT);
        SetShaderValue(rlgCtx->lightShader, light->locs.innerCutOff, &light->data.innerCutOff, SHADER_UNIFORM_FLOAT);
        SetShaderValue(rlgCtx->lightShader, light->locs.outerCutOff, &light->data.outerCutOff, SHADER_UNIFORM_FLOAT);
        SetShaderValue(rlgCtx->lightShader, light->locs.constant, &light->data.constant, SHADER_UNIFORM_FLOAT);
    }

    // Set light count
    rlgCtx->lightCount = count;

    // Load depth shader (used for shadow casting)
    rlgCtx->depthShader = LoadShaderFromMemory(rlgCachedDepthVS, rlgCachedDepthFS);

    // Load shadow map shader (used to render shadow maps)
    rlgCtx->shadowMapShader = LoadShaderFromMemory(rlgCachedShadowMapVS, rlgCachedShadowMapFS);

    rlgCtx->depthNear = 0.1f;
    rlgCtx->depthFar = 100.0f;

    rlgCtx->locDepthNear = GetShaderLocation(rlgCtx->shadowMapShader, "near");
    rlgCtx->locDepthFar = GetShaderLocation(rlgCtx->shadowMapShader, "far");

    SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->locDepthNear,
        &rlgCtx->depthNear, SHADER_UNIFORM_FLOAT);

    SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->locDepthFar,
        &rlgCtx->depthFar, SHADER_UNIFORM_FLOAT);

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
            struct RLG_Light *light = &pCtx->lights[i];

            if (light->data.shadowMap.id != 0)
            {
                rlUnloadTexture(light->data.shadowMap.depth.id);
                rlUnloadFramebuffer(light->data.shadowMap.id);
            }
        }

        free(pCtx->lights);
        pCtx->lights = NULL;
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
    rlgCtx->viewPos = position;
    SetShaderValue(rlgCtx->lightShader, rlgCtx->locViewPos,
        &rlgCtx->viewPos, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetViewPosition(void)
{
    return rlgCtx->viewPos;
}

void RLG_SetMap(RLG_MaterialMap map, bool active)
{
    int v = (int)active;

    switch (map)
    {
        case RLG_MAP_METALNESS:
            rlgCtx->material.data.useMetalnessMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.useMetalnessMap, &v, SHADER_UNIFORM_INT);
            break;

        case RLG_MAP_ROUGHNESS:
            rlgCtx->material.data.useRoughnessMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.useRoughnessMap, &v, SHADER_UNIFORM_INT);
            break;

        case RLG_MAP_OCCLUSION:
            rlgCtx->material.data.useOcclusionMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.useOcclusionMap, &v, SHADER_UNIFORM_INT);
            break;

        case RLG_MAP_EMISSIVE:
            rlgCtx->material.data.useEmissiveMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.useEmissiveMap, &v, SHADER_UNIFORM_INT);
            break;

        case RLG_MAP_NORMAL:
            rlgCtx->material.data.useNormalMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.useNormalMap, &v, SHADER_UNIFORM_INT);
            break;

        case RLG_MAP_HEIGHT:
            rlgCtx->material.data.useHeightMap = active;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.useHeightMap, &v, SHADER_UNIFORM_INT);
            break;

        default:
            break;
    }
}

bool RLG_IsMapEnabled(RLG_MaterialMap map)
{
    bool result = false;

    switch (map)
    {
        case RLG_MAP_METALNESS:
            result = rlgCtx->material.data.useMetalnessMap;
            break;

        case RLG_MAP_ROUGHNESS:
            result = rlgCtx->material.data.useRoughnessMap;
            break;

        case RLG_MAP_OCCLUSION:
            result = rlgCtx->material.data.useOcclusionMap;
            break;

        case RLG_MAP_EMISSIVE:
            result = rlgCtx->material.data.useEmissiveMap;
            break;

        case RLG_MAP_NORMAL:
            result = rlgCtx->material.data.useNormalMap;
            break;

        case RLG_MAP_HEIGHT:
            result = rlgCtx->material.data.useHeightMap;
            break;

        default:
            break;
    }

    return result;
}

void RLG_SetMaterialValue(RLG_MaterialProperty property, float value)
{
    switch (property)
    {
        case RLG_MAT_EMISSIVE_TINT:
            rlgCtx->material.data.colEmissive = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.colEmissive,
                &rlgCtx->material.data.colEmissive, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_AMBIENT_TINT:
            rlgCtx->material.data.colAmbient = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.colAmbient,
                &rlgCtx->material.data.colAmbient, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_METALNESS:
            rlgCtx->material.data.metalness = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.metalness,
                &value, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_MAT_ROUGHNESS:
            rlgCtx->material.data.roughness = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.roughness,
                &value, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_MAT_SPECULAR:
            rlgCtx->material.data.specular = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.specular,
                &rlgCtx->material.data.specular, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_MAT_HEIGHT_SCALE:
            rlgCtx->material.data.heightScale = value;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.heightScale,
                &rlgCtx->material.data.heightScale, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_MAT_HEIGHT_MIN_LAYERS:
            rlgCtx->material.data.parallaxMinLayers = (int)(value + 0.5f);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.parallaxMinLayers,
                &rlgCtx->material.data.parallaxMinLayers, SHADER_UNIFORM_INT);
            break;

        case RLG_MAT_HEIGHT_MAX_LAYERS:
            rlgCtx->material.data.parallaxMaxLayers = (int)(value + 0.5f);
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.parallaxMaxLayers,
                &rlgCtx->material.data.parallaxMaxLayers, SHADER_UNIFORM_INT);
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
        case RLG_MAT_EMISSIVE_TINT:
            rlgCtx->material.data.colEmissive = nCol;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.colEmissive,
                &nCol, SHADER_UNIFORM_VEC3);
            break;

        case RLG_MAT_AMBIENT_TINT:
            rlgCtx->material.data.colAmbient = nCol;
            SetShaderValue(rlgCtx->lightShader, rlgCtx->material.locs.colAmbient,
                &nCol, SHADER_UNIFORM_VEC3);
            break;

        default:
            break;
    }
}

float RLG_GetMaterialValue(RLG_MaterialProperty property)
{
    float result = 0.0f;

    switch (property)
    {
        case RLG_MAT_METALNESS:
            result = rlgCtx->material.data.metalness;
            break;

        case RLG_MAT_ROUGHNESS:
            result = rlgCtx->material.data.roughness;
            break;

        case RLG_MAT_SPECULAR:
            result = rlgCtx->material.data.specular;
            break;

        case RLG_MAT_HEIGHT_SCALE:
            result = rlgCtx->material.data.heightScale;
            break;

        case RLG_MAT_HEIGHT_MIN_LAYERS:
            result = rlgCtx->material.data.parallaxMinLayers;
            break;

        case RLG_MAT_HEIGHT_MAX_LAYERS:
            result = rlgCtx->material.data.parallaxMaxLayers;
            break;

        default:
            break;
    }

    return result;
}

Color RLG_GetMaterialColor(RLG_MaterialProperty property)
{
    Color result = BLACK;

    switch (property)
    {
        case RLG_MAT_EMISSIVE_TINT:
            result.r = (unsigned char)(255*rlgCtx->material.data.colEmissive.x);
            result.g = (unsigned char)(255*rlgCtx->material.data.colEmissive.y);
            result.b = (unsigned char)(255*rlgCtx->material.data.colEmissive.z);
            break;

        case RLG_MAT_AMBIENT_TINT:
            result.r = (unsigned char)(255*rlgCtx->material.data.colAmbient.x);
            result.g = (unsigned char)(255*rlgCtx->material.data.colAmbient.y);
            result.b = (unsigned char)(255*rlgCtx->material.data.colAmbient.z);
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

    struct RLG_Light *l = &rlgCtx->lights[light];

    l->data.enabled = (int)active;
    SetShaderValue(rlgCtx->lightShader, l->locs.enabled,
        &l->data.enabled, SHADER_UNIFORM_INT);
}

bool RLG_IsLightEnabled(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_IsLightEnabled' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return false;
    }

    return (bool)rlgCtx->lights[light].data.enabled;
}

void RLG_ToggleLight(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_ToggleLight' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    l->data.enabled = !l->data.enabled;
    SetShaderValue(rlgCtx->lightShader, l->locs.enabled,
        &l->data.enabled, SHADER_UNIFORM_INT);
}

void RLG_SetLightType(unsigned int light, RLG_LightType type)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightType' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    l->data.type = (int)type;
    SetShaderValue(rlgCtx->lightShader, l->locs.type,
        &l->data.type, SHADER_UNIFORM_INT);
}

RLG_LightType RLG_GetLightType(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightType' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return (RLG_LightType)0;
    }

    return (RLG_LightType)rlgCtx->lights[light].data.type;
}

void RLG_SetLightValue(unsigned int light, RLG_LightProperty property, float value)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightValue' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    switch (property)
    {
        case RLG_LIGHT_COLOR:
            l->data.color = (Vector3) { value, value, value };
            SetShaderValue(rlgCtx->lightShader, l->locs.color,
                &l->data.color, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_ENERGY:
            l->data.energy = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.energy,
                &l->data.energy, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_LIGHT_SPECULAR:
            l->data.specular = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.specular,
                &l->data.specular, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_LIGHT_SIZE:
            l->data.size = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.size,
                &l->data.size, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_LIGHT_INNER_CUTOFF:
            l->data.innerCutOff = cosf(value*DEG2RAD);
            SetShaderValue(rlgCtx->lightShader, l->locs.innerCutOff,
                &l->data.innerCutOff, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_LIGHT_OUTER_CUTOFF:
            l->data.outerCutOff = cosf(value*DEG2RAD);
            SetShaderValue(rlgCtx->lightShader, l->locs.outerCutOff,
                &l->data.outerCutOff, SHADER_UNIFORM_FLOAT);
            break;

        case RLG_LIGHT_ATTENUATION_CONSTANT:
            l->data.constant = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.constant, &value, SHADER_UNIFORM_FLOAT);

        case RLG_LIGHT_ATTENUATION_LINEAR:
            l->data.linear = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.linear, &value, SHADER_UNIFORM_FLOAT);

        case RLG_LIGHT_ATTENUATION_QUADRATIC:
            l->data.quadratic = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.quadratic, &value, SHADER_UNIFORM_FLOAT);
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

    struct RLG_Light *l = &rlgCtx->lights[light];
    Vector3 value = { x, y, z };

    switch (property)
    {
        case RLG_LIGHT_POSITION:
            l->data.position = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.position,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_DIRECTION:
            l->data.direction = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.direction,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_COLOR:
            l->data.color = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.color,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_ATTENUATION_CLQ:
            l->data.linear = y;
            l->data.constant = x;
            l->data.quadratic = z;
            SetShaderValue(rlgCtx->lightShader, l->locs.linear, &y, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, l->locs.constant, &x, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, l->locs.quadratic, &z, SHADER_UNIFORM_FLOAT);
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

    struct RLG_Light *l = &rlgCtx->lights[light];

    switch (property)
    {
        case RLG_LIGHT_POSITION:
            l->data.position = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.position,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_DIRECTION:
            l->data.direction = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.direction,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_COLOR:
            l->data.color = value;
            SetShaderValue(rlgCtx->lightShader, l->locs.color,
                &value, SHADER_UNIFORM_VEC3);
            break;

        case RLG_LIGHT_ATTENUATION_CLQ:
            l->data.linear = value.y;
            l->data.constant = value.x;
            l->data.quadratic = value.z;
            SetShaderValue(rlgCtx->lightShader, l->locs.linear, &value.y, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, l->locs.constant, &value.x, SHADER_UNIFORM_FLOAT);
            SetShaderValue(rlgCtx->lightShader, l->locs.quadratic, &value.z, SHADER_UNIFORM_FLOAT);
            break;

        default:
            break;
    }
}

void RLG_SetLightColor(unsigned int light, Color color)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightColor' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    Vector3 nCol = { 0 };
    nCol.x = color.r/255.0f;
    nCol.y = color.g/255.0f;
    nCol.z = color.b/255.0f;

    struct RLG_Light *l = &rlgCtx->lights[light];

    l->data.color = nCol;
    SetShaderValue(rlgCtx->lightShader, l->locs.color,
        &nCol, SHADER_UNIFORM_VEC3);
}

float RLG_GetLightValue(unsigned int light, RLG_LightProperty property)
{
    float result = 0;

    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightValue' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return result;
    }

    const struct RLG_Light *l = &rlgCtx->lights[light];

    switch (property)
    {
        case RLG_LIGHT_ENERGY:
            result = l->data.energy;
            break;

        case RLG_LIGHT_SPECULAR:
            result = l->data.specular;
            break;

        case RLG_LIGHT_SIZE:
            result = l->data.size;
            break;

        case RLG_LIGHT_INNER_CUTOFF:
            result = acosf(l->data.innerCutOff)*RAD2DEG;    // REVIEW: Store in degrees in RAM?
            break;

        case RLG_LIGHT_OUTER_CUTOFF:
            result = acosf(l->data.outerCutOff)*RAD2DEG;    // REVIEW: Store in degrees in RAM?
            break;

        case RLG_LIGHT_ATTENUATION_CONSTANT:
            result = l->data.constant;
            break;

        case RLG_LIGHT_ATTENUATION_LINEAR:
            result = l->data.linear;
            break;

        case RLG_LIGHT_ATTENUATION_QUADRATIC:
            result = l->data.quadratic;
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

    const struct RLG_Light *l = &rlgCtx->lights[light];

    switch (property)
    {
        case RLG_LIGHT_POSITION:
            result = l->data.position;
            break;

        case RLG_LIGHT_DIRECTION:
            result = l->data.direction;
            break;

        case RLG_LIGHT_COLOR:
            result = l->data.color;
            break;

        case RLG_LIGHT_ATTENUATION_CLQ:
            result.y = l->data.linear;
            result.x = l->data.constant;
            result.z = l->data.quadratic;
            break;

        default:
            break;
    }

    return result;
}

Color RLG_GetLightColor(unsigned int light)
{
    Color result = BLACK;

    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightColor' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return result;
    }

    const struct RLG_Light *l = &rlgCtx->lights[light];

    result.r = 255*l->data.color.x;
    result.g = 255*l->data.color.y;
    result.b = 255*l->data.color.z;

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

    l->data.position.x += x;
    l->data.position.y += y;
    l->data.position.z += z;

    SetShaderValue(rlgCtx->lightShader, l->locs.position,
        &l->data.position, SHADER_UNIFORM_VEC3);
}

void RLG_LightTranslateV(unsigned int light, Vector3 v)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightTranslateV' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];
    l->data.position.x += v.x;
    l->data.position.y += v.y;
    l->data.position.z += v.z;

    SetShaderValue(rlgCtx->lightShader, l->locs.position,
        &l->data.position, SHADER_UNIFORM_VEC3);
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

    l->data.direction.y = l->data.direction.y*c + l->data.direction.z*s;
    l->data.direction.z = -l->data.direction.y*s + l->data.direction.z*c;

    SetShaderValue(rlgCtx->lightShader, l->locs.direction,
        &l->data.direction, SHADER_UNIFORM_VEC3);
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

    l->data.direction.x = l->data.direction.x*c - l->data.direction.z*s;
    l->data.direction.z = l->data.direction.x*s + l->data.direction.z*c;

    SetShaderValue(rlgCtx->lightShader, l->locs.direction,
        &l->data.direction, SHADER_UNIFORM_VEC3);
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

    l->data.direction.x = l->data.direction.x*c + l->data.direction.y*s;
    l->data.direction.y = -l->data.direction.x*s + l->data.direction.y*c;

    SetShaderValue(rlgCtx->lightShader, l->locs.direction,
        &l->data.direction, SHADER_UNIFORM_VEC3);
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
        l->data.direction.x,
        l->data.direction.y,
        l->data.direction.z,
        0.0f
    };

    // Calculate the rotated direction quaternion
    Quaternion rotatedQuat = QuaternionMultiply(
        QuaternionMultiply(rotationQuat, directionQuat),
        QuaternionInvert(rotationQuat));

    // Update the light direction with the rotated direction
    l->data.direction = Vector3Normalize((Vector3) {
        rotatedQuat.x, rotatedQuat.y, rotatedQuat.z
    });

    SetShaderValue(rlgCtx->lightShader, l->locs.direction,
        &l->data.direction, SHADER_UNIFORM_VEC3);
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

    struct RLG_Light *l = &rlgCtx->lights[light];

    l->data.direction = Vector3Normalize(Vector3Subtract(
        targetPosition, l->data.position));

    SetShaderValue(rlgCtx->lightShader, l->locs.direction,
        &l->data.direction, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetLightTarget(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightTarget' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return (Vector3) { 0 };
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    return Vector3Add(
        l->data.position,
        l->data.direction);
}

void RLG_EnableShadow(unsigned int light, int shadowMapResolution)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_EnableShadow' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    if (l->data.type == RLG_OMNILIGHT)
    {
        TraceLog(LOG_WARNING, "The light [ID %i] is of type 'RLG_OMNILIGHT', shadow support for omnilights is not yet implemented, so please specify the light direction.", light, rlgCtx->lightCount);
    }

    if (l->data.shadowMap.width != shadowMapResolution)  ///< TODO: Review for CSM
    {
        if (l->data.shadowMap.id != 0)
        {
            rlUnloadTexture(l->data.shadowMap.depth.id);
            rlUnloadFramebuffer(l->data.shadowMap.id);
        }

        struct RLG_ShadowMap *sm = &l->data.shadowMap;

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
        SetShaderValue(rlgCtx->lightShader, l->locs.shadowMapTxlSz,
            &texelSize, SHADER_UNIFORM_FLOAT);

        // NOTE: This is a rough approximation, other factors may affect this variable.
        //       A better approach would be to calculate the bias in the shader,
        //       taking into account factors such as the distance between the
        //       light and the fragment position.
        l->data.depthBias = 0.1f*shadowMapResolution*tan(acosf(l->data.outerCutOff));
        SetShaderValue(rlgCtx->lightShader, l->locs.depthBias,
            &l->data.depthBias, SHADER_UNIFORM_FLOAT);
    }

    l->data.shadow = 1;
    SetShaderValue(rlgCtx->lightShader, l->locs.shadow,
        &l->data.shadow, SHADER_UNIFORM_INT);
}

void RLG_DisableShadow(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_DisableShadow' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    l->data.shadow = 0;
    SetShaderValue(rlgCtx->lightShader, l->locs.shadow,
        &l->data.shadow, SHADER_UNIFORM_INT);
}

bool RLG_IsShadowEnabled(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_IsShadowEnabled' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return false;
    }

    return rlgCtx->lights[light].data.shadow;
}

void RLG_SetShadowBias(unsigned int light, float value)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetShadowBias' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return;
    }

    struct RLG_Light *l = &rlgCtx->lights[light];

    l->data.depthBias = value;
    SetShaderValue(rlgCtx->lightShader, l->locs.depthBias,
        &value, SHADER_UNIFORM_FLOAT);
}

float RLG_GetShadowBias(unsigned int light)
{
    if (light >= rlgCtx->lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetShadowBias' exceeds allocated number [MAX %i]", light, rlgCtx->lightCount);
        return 0;
    }

    return rlgCtx->lights[light].data.depthBias;
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

    if (!l->data.shadow)
    {
        TraceLog(LOG_ERROR, "Light does not support shadow casting. Light ID: [%i]", light);
        return;
    }

    rlDrawRenderBatchActive();
    rlEnableFramebuffer(l->data.shadowMap.id);

    rlViewport(0, 0, l->data.shadowMap.width, l->data.shadowMap.height);

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();

#   define NEAR .01     // TODO: replace with rlGetCullDistanceNear()
#   define FAR 1000.    // TODO: replace with rlGetCullDistanceFar()

    // TODO: Review for CSM (aspect ratio ?)
    // NOTE: acos(outerCutoff) works only with spotlight
    double bound = NEAR*tan(acosf(l->data.outerCutOff));
    rlFrustum(-bound, bound, -bound, bound, NEAR, FAR);

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
//
    Matrix matView = MatrixLookAt(l->data.position, Vector3Add(l->data.position, l->data.direction), (Vector3){ 0, 1, 0 });
    rlMultMatrixf(MatrixToFloat(matView));
//
    rlEnableDepthTest();
    rlDisableColorBlend();
//
    Matrix viewProj = MatrixMultiply(matView, rlGetMatrixProjection());
    SetShaderValueMatrix(rlgCtx->lightShader, l->locs.vpMatrix, viewProj);
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

    if (near != rlgCtx->depthNear)
    {
        rlgCtx->depthNear = near;
        SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->locDepthNear,
            &rlgCtx->depthNear, SHADER_UNIFORM_FLOAT);
    }

    if (far != rlgCtx->depthFar)
    {
        rlgCtx->depthFar = far;
        SetShaderValue(rlgCtx->shadowMapShader, rlgCtx->locDepthFar,
            &rlgCtx->depthFar, SHADER_UNIFORM_FLOAT);
    }

    BeginShaderMode(rlgCtx->shadowMapShader);
    rlBegin(RL_QUADS);

        rlSetTexture(rlgCtx->lights[light].data.shadowMap.depth.id);

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
    // Upload to shader material.data.colDiffuse
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

    // Upload to shader material.data.colSpecular (if location available)
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
        const struct RLG_Light *l = &rlgCtx->lights[i];

        if (l->data.shadow)
        {
            int j = 11 + i;
            rlActiveTextureSlot(j);
            rlEnableTexture(l->data.shadowMap.depth.id);
            rlSetUniform(l->locs.shadowMap, &j, SHADER_UNIFORM_INT, 1);
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
        if (rlgCtx->lights[i].data.shadow)
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