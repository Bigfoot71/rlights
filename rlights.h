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

typedef enum {
    RLG_DIRECTIONAL,
    RLG_OMNILIGHT,
    RLG_SPOTLIGHT
} RLG_LightType;

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Initialize rlights with the desired lights number.
 * 
 * @param lightCount The number of lights to initialize in.
 */
void RLG_Init(unsigned int lightCount);

/**
 * @brief Close the rlights and release any allocated resources.
 */
void RLG_Close(void);

/**
 * @brief Set custom lighting shader code.
 * 
 * @note This function should be called before RLG_Init to define your own lighting shaders.
 * 
 * @param vsCode Vertex shader code for lighting.
 * @param fsCode Fragment shader code for lighting.
 */
void RLG_SetLightingShaderCode(const char *vsCode, const char *fsCode);

/**
 * @brief Set custom depth shader code.
 * 
 * @note This function should be called before RLG_Init to define your own depth shaders.
 * 
 * @param vsCode Vertex shader code for depth.
 * @param fsCode Fragment shader code for depth.
 */
void RLG_SetDepthShaderCode(const char *vsCode, const char *fsCode);

/**
 * @brief Set custom shadow map shader code.
 * 
 * @note This function should be called before RLG_Init to define your own shadow map shaders.
 * 
 * @param vsCode Vertex shader code for shadow mapping.
 * @param fsCode Fragment shader code for shadow mapping.
 */
void RLG_SetShadowMapShaderCode(const char *vsCode, const char *fsCode);

/**
 * @brief Get the current lighting shader.
 * 
 * @return A pointer to the current Shader used for lighting.
 */
const Shader* RLG_GetLightShader(void);

/**
 * @brief Get the current depth shader.
 * 
 * @return A pointer to the current Shader used for depth rendering.
 */
const Shader* RLG_GetDepthShader(void);

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
 * @brief Enable the specular map in the shader.
 */
void RLG_EnableSpecularMap(void);

/**
 * @brief Disable the specular map in the shader.
 */
void RLG_DisableSpecularMap(void);

/**
 * @brief Check if the specular map is enabled.
 * 
 * @return true if the specular map is enabled, false otherwise.
 */
bool RLG_IsSpecularMapEnabled(void);

/**
 * @brief Enable the normal map in the shader.
 */
void RLG_EnableNormalMap(void);

/**
 * @brief Disable the normal map in the shader.
 */
void RLG_DisableNormalMap(void);

/**
 * @brief Check if the normal map is enabled.
 * 
 * @return true if the normal map is enabled, false otherwise.
 */
bool RLG_IsNormalMapEnabled(void);

/**
 * @brief Set the shininess value for specular highlights.
 * 
 * @param value The shininess value.
 */
void RLG_SetShininess(float value);

/**
 * @brief Get the current shininess value for specular highlights.
 * 
 * @return The current shininess value.
 */
float RLG_GetShininess(void);

/**
 * @brief Set the specular color in the shader.
 * 
 * @param r The red component of the specular color.
 * @param g The green component of the specular color.
 * @param b The blue component of the specular color.
 */
void RLG_SetSpecular(float r, float g, float b);

/**
 * @brief Set the specular color in the shader using a Vector3 structure.
 * 
 * @param color The specular color as a Vector3 structure.
 */
void RLG_SetSpecularV(Vector3 color);

/**
 * @brief Set the specular color for the shader using a Color structure.
 * 
 * @param color The specular color as a Color structure.
 */
void RLG_SetSpecularC(Color color);

/**
 * @brief Get the current specular color sets in the shader.
 * 
 * @return The current specular color as a Vector3 structure.
 */
Vector3 RLG_GetSpecular(void);

/**
 * @brief Get the current specular color sets in the shader as a Color structure.
 * 
 * @return The current specular color as a Color structure.
 */
Color RLG_GetSpecularC(void);

/**
 * @brief Set the ambient color in the shader.
 * 
 * @param r The red component of the ambient color.
 * @param g The green component of the ambient color.
 * @param b The blue component of the ambient color.
 */
void RLG_SetAmbient(float r, float g, float b);

/**
 * @brief Set the ambient color in the shader using a Vector3 structure.
 * 
 * @param color The ambient color as a Vector3 structure.
 */
void RLG_SetAmbientV(Vector3 color);

/**
 * @brief Set the ambient color in the shader using a Color structure.
 * 
 * @param color The ambient color as a Color structure.
 */
void RLG_SetAmbientC(Color color);

/**
 * @brief Get the current ambient color sets in the shader
 * 
 * @return The current ambient color as a Vector3 structure.
 */
Vector3 RLG_GetAmbient(void);

/**
 * @brief Get the current ambient color sets in the shader as a Color structure.
 * 
 * @return The current ambient color as a Color structure.
 */
Color RLG_GetAmbientC(void);

/**
 * @brief Get the number of lights initialized sets in the shader.
 * 
 * @return The number of lights as an unsigned integer.
 */
unsigned int RLG_GetLightcount(void);

/**
 * @brief Toggle the state of a specific light.
 * 
 * @param light The index of the light to toggle.
 */
void RLG_ToggleLight(unsigned int light);

/**
 * @brief Enable a specific light.
 * 
 * @param light The index of the light to enable.
 */
void RLG_EnableLight(unsigned int light);

/**
 * @brief Disable a specific light.
 * 
 * @param light The index of the light to disable.
 */
void RLG_DisableLight(unsigned int light);

/**
 * @brief Check if a specific light is enabled.
 * 
 * @param light The index of the light to check.
 * @return true if the light is enabled, false otherwise.
 */
bool RLG_IsLightEnabled(unsigned int light);

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
 * @brief Set the position of a specific light.
 * 
 * @param light The index of the light to set the position for.
 * @param x The x-coordinate of the light position.
 * @param y The y-coordinate of the light position.
 * @param z The z-coordinate of the light position.
 */
void RLG_SetLightPosition(unsigned int light, float x, float y, float z);

/**
 * @brief Set the position of a specific light using a Vector3 structure.
 * 
 * @param light The index of the light to set the position for.
 * @param position The position of the light as a Vector3 structure.
 */
void RLG_SetLightPositionV(unsigned int light, Vector3 position);

/**
 * @brief Get the position of a specific light.
 * 
 * @param light The index of the light to get the position for.
 * @return The position of the light as a Vector3 structure.
 */
Vector3 RLG_GetLightPosition(unsigned int light);

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
 * @brief Set the direction of a specific light.
 * 
 * @param light The index of the light to set the direction for.
 * @param x The x-component of the light direction.
 * @param y The y-component of the light direction.
 * @param z The z-component of the light direction.
 */
void RLG_SetLightDirection(unsigned int light, float x, float y, float z);

/**
 * @brief Set the direction of a specific light using a Vector3 structure.
 * 
 * @param light The index of the light to set the direction for.
 * @param direction The direction of the light as a Vector3 structure.
 */
void RLG_SetLightDirectionV(unsigned int light, Vector3 direction);

/**
 * @brief Get the direction of a specific light.
 * 
 * @param light The index of the light to get the direction for.
 * @return The direction of the light as a Vector3 structure.
 */
Vector3 RLG_GetLightDirection(unsigned int light);

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
 * @brief Set the diffuse color of a specific light.
 * 
 * @param light The index of the light to set the diffuse color for.
 * @param r The red component of the diffuse color.
 * @param g The green component of the diffuse color.
 * @param b The blue component of the diffuse color.
 */
void RLG_SetLightDiffuse(unsigned int light, float r, float g, float b);

/**
 * @brief Set the diffuse color of a specific light using a Vector3 structure.
 * 
 * @param light The index of the light to set the diffuse color for.
 * @param color The diffuse color as a Vector3 structure.
 */
void RLG_SetLightDiffuseV(unsigned int light, Vector3 color);

/**
 * @brief Set the diffuse color of a specific light using a Color structure.
 * 
 * @param light The index of the light to set the diffuse color for.
 * @param color The diffuse color as a Color structure.
 */
void RLG_SetLightDiffuseC(unsigned int light, Color color);

/**
 * @brief Get the diffuse color of a specific light.
 * 
 * @param light The index of the light to get the diffuse color for.
 * @return The diffuse color as a Vector3 structure.
 */
Vector3 RLG_GetLightDiffuse(unsigned int light);

/**
 * @brief Get the diffuse color of a specific light as a Color structure.
 * 
 * @param light The index of the light to get the diffuse color for.
 * @return The diffuse color as a Color structure.
 */
Color RLG_GetLightDiffuseC(unsigned int light);

/**
 * @brief Set the specular color of a specific light.
 * 
 * @param light The index of the light to set the specular color for.
 * @param r The red component of the specular color.
 * @param g The green component of the specular color.
 * @param b The blue component of the specular color.
 */
void RLG_SetLightSpecular(unsigned int light, float r, float g, float b);

/**
 * @brief Set the specular color of a specific light using a Vector3 structure.
 * 
 * @param light The index of the light to set the specular color for.
 * @param color The specular color as a Vector3 structure.
 */
void RLG_SetLightSpecularV(unsigned int light, Vector3 color);

/**
 * @brief Set the specular color of a specific light using a Color structure.
 * 
 * @param light The index of the light to set the specular color for.
 * @param color The specular color as a Color structure.
 */
void RLG_SetLightSpecularC(unsigned int light, Color color);

/**
 * @brief Get the specular color of a specific light.
 * 
 * @param light The index of the light to get the specular color for.
 * @return The specular color as a Vector3 structure.
 */
Vector3 RLG_GetLightSpecular(unsigned int light);

/**
 * @brief Get the specular color of a specific light as a Color structure.
 * 
 * @param light The index of the light to get the specular color for.
 * @return The specular color as a Color structure.
 */
Color RLG_GetLightSpecularC(unsigned int light);

/**
 * @brief Set the inner cutoff angle of a spotlight.
 * 
 * @note These functions are only applicable to spotlight types.
 * 
 * @param light The index of the spotlight to set the inner cutoff angle for.
 * @param degrees The inner cutoff angle in degrees.
 */
void RLG_SetLightInnerCutOff(unsigned int light, float degrees);

/**
 * @brief Get the inner cutoff angle of a spotlight.
 * 
 * @note These functions are only applicable to spotlight types.
 * 
 * @param light The index of the spotlight to get the inner cutoff angle for.
 * @return The inner cutoff angle in degrees.
 */
float RLG_GetLightInnerCutoff(unsigned int light);

/**
 * @brief Set the outer cutoff angle of a spotlight.
 * 
 * @note These functions are only applicable to spotlight types.
 * 
 * @param light The index of the spotlight to set the outer cutoff angle for.
 * @param degrees The outer cutoff angle in degrees.
 */
void RLG_SetLightOuterCutOff(unsigned int light, float degrees);

/**
 * @brief Get the outer cutoff angle of a spotlight.
 * 
 * @note These functions are only applicable to spotlight types.
 * 
 * @param light The index of the spotlight to get the outer cutoff angle for.
 * @return The outer cutoff angle in degrees.
 */
float RLG_GetLightOuterCutoff(unsigned int light);

/**
 * @brief Set the attenuation factors of a light.
 * 
 * @param light The index of the light to set the attenuation for.
 * @param constant The constant attenuation factor.
 * @param linear The linear attenuation factor.
 * @param quadratic The quadratic attenuation factor.
 */
void RLG_SetLightAttenuation(unsigned int light, float constant, float linear, float quadratic);

/**
 * @brief Get the attenuation factors of a light.
 * 
 * @param light The index of the light to get the attenuation factors for.
 * @param constant Pointer to store the constant attenuation factor.
 * @param linear Pointer to store the linear attenuation factor.
 * @param quadratic Pointer to store the quadratic attenuation factor.
 */
void RLG_GetLightAttenuation(unsigned int light, float* constant, float* linear, float* quadratic);

/**
 * @brief Set the quadratic attenuation factor of a light.
 * 
 * @param light The index of the light to set the quadratic attenuation factor for.
 * @param quadratic The quadratic attenuation factor.
 */
void RLG_SetLightAttenuationQuadratic(unsigned int light, float quadratic);

/**
 * @brief Set the constant attenuation factor of a light.
 * 
 * @param light The index of the light to set the constant attenuation factor for.
 * @param constant The constant attenuation factor.
 */
void RLG_SetLightAttenuationConstant(unsigned int light, float constant);

/**
 * @brief Set the linear attenuation factor of a light.
 * 
 * @param light The index of the light to set the linear attenuation factor for.
 * @param linear The linear attenuation factor.
 */
void RLG_SetLightAttenuationLinear(unsigned int light, float linear);

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
void RLG_EnableLightShadow(unsigned int light, int shadowMapResolution);

/**
 * @brief Disable shadow casting for a light.
 * 
 * @param light The index of the light to disable shadow casting for.
 */
void RLG_DisableLightShadow(unsigned int light);

/**
 * @brief Check if shadow casting is enabled for a light.
 * 
 * @param light The index of the light to check for shadow casting.
 * @return true if shadow casting is enabled, false otherwise.
 */
bool RLG_IsLightShadowEnabled(unsigned int light);

/**
 * @brief Set the bias value for shadow mapping of a light.
 * 
 * @param light The index of the light to set the shadow bias for.
 * @param value The bias value to set.
 */
void RLG_SetLightShadowBias(unsigned int light, float value);

/**
 * @brief Get the bias value for shadow mapping of a light.
 * 
 * @param light The index of the light to get the shadow bias for.
 * @return The shadow bias value.
 */
float RLG_GetLightShadowBias(unsigned int light);

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
    "uniform lowp int useNormalMap;"

    "uniform sampler2D texture0;"   // diffuse
    "uniform sampler2D texture1;"   // specular
    "uniform sampler2D texture2;"   // normal

    "uniform vec3 colSpecular;"     // sent by rlights
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

        // ambient
        "vec3 ambientColor = colAmbient*diffSample;"

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

        GLSL_FINAL_COLOR("vec4(ambientColor + finalColor, 1.0)")
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
    int colAmbient;
    int viewPos;
    int shininess;

    int useSpecularMap;
    int useNormalMap;
};

struct RLG_GlobalLight
{
    Vector3 colSpecular;
    Vector3 colAmbient;
    Vector3 viewPos;
    float shininess;

    int useSpecularMap;
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
RLG = { 0 };

#ifndef NO_EMBEDDED_SHADERS
    static const char *rlgCachedLightVS     = rlgLightVS;
    static const char *rlgCachedLightFS     = rlgLightFS;
    static const char *rlgCachedDepthVS     = rlgDepthVS;
    static const char *rlgCachedDepthFS     = rlgDepthFS;
    static const char *rlgCachedShadowMapVS = NULL;
    static const char *rlgCachedShadowMapFS = rlgShadowMapFS;
#else
    static const char *rlgCachedLightVS     = NULL;
    static const char *rlgCachedLightFS     = NULL;
    static const char *rlgCachedDepthVS     = NULL;
    static const char *rlgCachedDepthFS     = NULL;
    static const char *rlgCachedShadowMapVS = NULL;
    static const char *rlgCachedShadowMapFS = NULL;
#endif //NO_EMBEDDED_SHADERS

/* Public API */

void RLG_Init(unsigned int count)
{
    if (RLG.lights != NULL)
    {
        TraceLog(LOG_ERROR, "You are trying to initialize rlights when it has already been initialized.");
        return;
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
    RLG.lightShader = LoadShaderFromMemory(lightVS, lightFS);

#   ifndef NO_EMBEDDED_SHADERS
#   if GLSL_VERSION > 100
    if (vsFormated) free((void*)lightVS);
#   endif
    if (fsFormated) free((void*)lightFS);
#   endif //NO_EMBEDDED_SHADERS

    // Retrieving global shader locations
    RLG.locsGlobalLight.useSpecularMap = GetShaderLocation(RLG.lightShader, "useSpecularMap");
    RLG.locsGlobalLight.useNormalMap = GetShaderLocation(RLG.lightShader, "useNormalMap");
    RLG.locsGlobalLight.colSpecular = GetShaderLocation(RLG.lightShader, "colSpecular");
    RLG.locsGlobalLight.colAmbient = GetShaderLocation(RLG.lightShader, "colAmbient");
    RLG.locsGlobalLight.shininess = GetShaderLocation(RLG.lightShader, "shininess");
    RLG.locsGlobalLight.viewPos = GetShaderLocation(RLG.lightShader, "viewPos");

    // Define default global uniforms
    RLG.globalLight = (struct RLG_GlobalLight) { 0 };
    RLG.globalLight.colSpecular = (Vector3) { 1.0f, 1.0f, 1.0f };
    RLG.globalLight.colAmbient = (Vector3) { 0.1f, 0.1f, 0.1f };
    RLG.globalLight.shininess = 32.0f;

    // Send default globals uniforms (no need to send zero-values)
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colSpecular, &RLG.globalLight.colSpecular, SHADER_UNIFORM_VEC3);
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colAmbient, &RLG.globalLight.colAmbient, SHADER_UNIFORM_VEC3);
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.shininess, &RLG.globalLight.shininess, SHADER_UNIFORM_FLOAT);

    // Allocation and initialization of the desired number of lights
    RLG.lights = (struct RLG_Light*)malloc(count*sizeof(struct RLG_Light));
    RLG.locsLights = (struct RLG_LightLocs*)malloc(count*sizeof(struct RLG_LightLocs));
    for (int i = 0; i < count; i++)
    {
        struct RLG_Light *light = &RLG.lights[i];
        struct RLG_LightLocs *locs = &RLG.locsLights[i];

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

        locs->vpMatrix       = GetShaderLocation(RLG.lightShader, TextFormat("matLights[%i]", i));
        locs->shadowMap      = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].shadowMap", i));
        locs->position       = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].position", i));
        locs->direction      = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].direction", i));
        locs->diffuse        = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].diffuse", i));
        locs->specular       = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].specular", i));
        locs->innerCutOff    = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].innerCutOff", i));
        locs->outerCutOff    = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].outerCutOff", i));
        locs->constant       = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].constant", i));
        locs->linear         = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].linear", i));
        locs->quadratic      = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].quadratic", i));
        locs->shadowMapTxlSz = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].shadowMapTxlSz", i));
        locs->depthBias      = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].depthBias", i));
        locs->type           = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].type", i));
        locs->shadow         = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].shadow", i));
        locs->enabled        = GetShaderLocation(RLG.lightShader, TextFormat("lights[%i].enabled", i));

        SetShaderValue(RLG.lightShader, locs->diffuse, &light->diffuse, SHADER_UNIFORM_VEC3);
        SetShaderValue(RLG.lightShader, locs->specular, &light->specular, SHADER_UNIFORM_VEC3);
        SetShaderValue(RLG.lightShader, locs->innerCutOff, &light->innerCutOff, SHADER_UNIFORM_FLOAT);
        SetShaderValue(RLG.lightShader, locs->outerCutOff, &light->outerCutOff, SHADER_UNIFORM_FLOAT);
        SetShaderValue(RLG.lightShader, locs->constant, &light->constant, SHADER_UNIFORM_FLOAT);
    }

    // Set light count
    RLG.lightCount = count;

    // Load depth shader (used for shadow casting)
    RLG.depthShader = LoadShaderFromMemory(rlgCachedDepthVS, rlgCachedDepthFS);

    // Load shadow map shader (used to render shadow maps)
    RLG.shadowMapShader = LoadShaderFromMemory(rlgCachedShadowMapVS, rlgCachedShadowMapFS);

    RLG.shadowMapShaderData.near = 0.1f;
    RLG.shadowMapShaderData.far = 100.0f;

    RLG.shadowMapShaderData.locNear = GetShaderLocation(RLG.shadowMapShader, "near");
    RLG.shadowMapShaderData.locFar = GetShaderLocation(RLG.shadowMapShader, "far");

    SetShaderValue(RLG.shadowMapShader, RLG.shadowMapShaderData.locNear,
        &RLG.shadowMapShaderData.near, SHADER_UNIFORM_FLOAT);

    SetShaderValue(RLG.shadowMapShader, RLG.shadowMapShaderData.locFar,
        &RLG.shadowMapShaderData.far, SHADER_UNIFORM_FLOAT);
}

void RLG_Close(void)
{
    if (IsShaderReady(RLG.lightShader))
    {
        UnloadShader(RLG.lightShader);
        RLG.lightShader = (Shader) { 0 };
    }

    if (IsShaderReady(RLG.depthShader))
    {
        UnloadShader(RLG.depthShader);
        RLG.depthShader = (Shader) { 0 };
    }

    if (IsShaderReady(RLG.shadowMapShader))
    {
        UnloadShader(RLG.shadowMapShader);
        RLG.shadowMapShader = (Shader) { 0 };
    }

    if (RLG.lights != NULL)
    {
        for (int i = 0; i < RLG.lightCount; i++)
        {
            if (RLG.lights[i].shadowMap.id != 0)
            {
                rlUnloadTexture(RLG.lights[i].shadowMap.depth.id);
                rlUnloadFramebuffer(RLG.lights[i].shadowMap.id);
            }
        }

        free(RLG.lights);
        RLG.lights = NULL;
    }

    if (RLG.locsLights != NULL)
    {
        free(RLG.locsLights);
        RLG.locsLights = NULL;
    }

    RLG.lightCount = 0;
}

void RLG_SetLightingShaderCode(const char *vsCode, const char *fsCode)
{
    rlgCachedLightVS = vsCode;
    rlgCachedLightFS = fsCode;
}

void RLG_SetDepthShaderCode(const char *vsCode, const char *fsCode)
{
    rlgCachedDepthVS = vsCode;
    rlgCachedDepthFS = fsCode;
}

void RLG_SetShadowMapShaderCode(const char *vsCode, const char *fsCode)
{
    rlgCachedShadowMapVS = vsCode;
    rlgCachedShadowMapFS = fsCode;
}

const Shader* RLG_GetLightShader(void)
{
    if (IsShaderReady(RLG.lightShader))
    {
        return &RLG.lightShader;
    }

    return NULL;
}

const Shader* RLG_GetDepthShader(void)
{
    if (IsShaderReady(RLG.depthShader))
    {
        return &RLG.depthShader;
    }

    return NULL;
}

void RLG_SetViewPosition(float x, float y, float z)
{
    RLG_SetViewPositionV((Vector3) { x, y, z });
}

void RLG_SetViewPositionV(Vector3 position)
{
    RLG.globalLight.viewPos = position;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.viewPos,
        &RLG.globalLight.viewPos, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetViewPosition(void)
{
    return RLG.globalLight.viewPos;
}

void RLG_EnableSpecularMap(void)
{
    const int v = 1;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.useSpecularMap, &v, SHADER_UNIFORM_INT);
}

void RLG_DisableSpecularMap(void)
{
    const int v = 0;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.useSpecularMap, &v, SHADER_UNIFORM_INT);
}

bool RLG_IsSpecularMapEnabled(void)
{
    return RLG.globalLight.useSpecularMap;
}

void RLG_EnableNormalMap(void)
{
    const int v = 1;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.useNormalMap, &v, SHADER_UNIFORM_INT);
}

void RLG_DisableNormalMap(void)
{
    const int v = 0;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.useNormalMap, &v, SHADER_UNIFORM_INT);
}

bool RLG_IsNormalMapEnabled(void)
{
    return RLG.globalLight.useNormalMap;
}

void RLG_SetShininess(float value)
{
    RLG.globalLight.shininess = value;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.shininess,
        &RLG.globalLight.shininess, SHADER_UNIFORM_FLOAT);
}

float RLG_GetShininess(void)
{
    return RLG.globalLight.shininess;
}

void RLG_SetSpecular(float r, float g, float b)
{
    RLG.globalLight.colSpecular = (Vector3) { r, g, b };
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colSpecular,
        &RLG.globalLight.colSpecular, SHADER_UNIFORM_VEC3);
}

void RLG_SetSpecularV(Vector3 color)
{
    RLG.globalLight.colSpecular = color;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colSpecular,
        &RLG.globalLight.colSpecular, SHADER_UNIFORM_VEC3);
}

void RLG_SetSpecularC(Color color)
{
    RLG.globalLight.colSpecular = (Vector3) {
        (float)color.r*(1.0f/255),
        (float)color.g*(1.0f/255),
        (float)color.b*(1.0f/255)
    };

    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colSpecular,
        &RLG.globalLight.colSpecular, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetSpecular(void)
{
    return RLG.globalLight.colSpecular;
}

Color RLG_GetSpecularC(void)
{
    return (Color) {
        (unsigned char)(255*RLG.globalLight.colSpecular.x),
        (unsigned char)(255*RLG.globalLight.colSpecular.y),
        (unsigned char)(255*RLG.globalLight.colSpecular.z),
        255
    };
}

void RLG_SetAmbient(float r, float g, float b)
{
    RLG.globalLight.colAmbient = (Vector3) { r, g, b };
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colAmbient,
        &RLG.globalLight.colAmbient, SHADER_UNIFORM_VEC3);
}

void RLG_SetAmbientV(Vector3 color)
{
    RLG.globalLight.colAmbient = color;
    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colAmbient,
        &RLG.globalLight.colAmbient, SHADER_UNIFORM_VEC3);
}

void RLG_SetAmbientC(Color color)
{
    RLG.globalLight.colAmbient = (Vector3) {
        (float)color.r*(1.0f/255),
        (float)color.g*(1.0f/255),
        (float)color.b*(1.0f/255)
    };

    SetShaderValue(RLG.lightShader, RLG.locsGlobalLight.colAmbient,
        &RLG.globalLight.colAmbient, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetAmbient(void)
{
    return RLG.globalLight.colAmbient;
}

Color RLG_GetAmbientC(void)
{
    return (Color) {
        (unsigned char)(255*RLG.globalLight.colAmbient.x),
        (unsigned char)(255*RLG.globalLight.colAmbient.y),
        (unsigned char)(255*RLG.globalLight.colAmbient.z),
        255
    };
}

unsigned int RLG_GetLightcount(void)
{
    return RLG.lightCount;
}

void RLG_ToggleLight(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_ToggleLight' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].enabled = !RLG.lights[light].enabled;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].enabled,
        &RLG.lights[light].enabled, SHADER_UNIFORM_INT);
}

void RLG_EnableLight(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_EnableLight' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].enabled = 1;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].enabled,
        &RLG.lights[light].enabled, SHADER_UNIFORM_INT);
}

void RLG_DisableLight(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_DisableLight' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].enabled = 0;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].enabled,
        &RLG.lights[light].enabled, SHADER_UNIFORM_INT);
}

bool RLG_IsLightEnabled(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_IsLightEnabled' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return false;
    }

    return (bool)RLG.lights[light].enabled;
}

void RLG_SetLightType(unsigned int light, RLG_LightType type)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightType' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].type = (int)type;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].type,
        &RLG.lights[light].type, SHADER_UNIFORM_INT);
}

RLG_LightType RLG_GetLightType(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightType' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return (RLG_LightType)0;
    }

    return (RLG_LightType)RLG.lights[light].type;
}

void RLG_LightTranslate(unsigned int light, float x, float y, float z)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightTranslate' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];
    l->position.x += x;
    l->position.y += y;
    l->position.z += z;

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].position,
        &l->position, SHADER_UNIFORM_VEC3);
}

void RLG_LightTranslateV(unsigned int light, Vector3 v)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightTranslateV' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];
    l->position.x += v.x;
    l->position.y += v.y;
    l->position.z += v.z;

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].position,
        &l->position, SHADER_UNIFORM_VEC3);
}

void RLG_SetLightPosition(unsigned int light, float x, float y, float z)
{
    RLG_SetLightPositionV(light, (Vector3) { x, y, z });
}

void RLG_SetLightPositionV(unsigned int light, Vector3 position)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightPosition' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].position = position;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].position,
        &RLG.lights[light].position, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetLightPosition(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightPosition' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return (Vector3) { 0 };
    }

    return RLG.lights[light].position;
}

void RLG_LightRotateX(unsigned int light, float degrees)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotateX' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];
    float radians = DEG2RAD*degrees;
    float c = cosf(radians);
    float s = sinf(radians);

    l->direction.y = l->direction.y*c + l->direction.z*s;
    l->direction.z = -l->direction.y*s + l->direction.z*c;

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].direction,
        &RLG.lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_LightRotateY(unsigned int light, float degrees)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotateY' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];
    float radians = DEG2RAD*degrees;
    float c = cosf(radians);
    float s = sinf(radians);

    l->direction.x = l->direction.x*c - l->direction.z*s;
    l->direction.z = l->direction.x*s + l->direction.z*c;

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].direction,
        &RLG.lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_LightRotateZ(unsigned int light, float degrees)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotateZ' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];
    float radians = DEG2RAD*degrees;
    float c = cosf(radians);
    float s = sinf(radians);

    l->direction.x = l->direction.x*c + l->direction.y*s;
    l->direction.y = -l->direction.x*s + l->direction.y*c;

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].direction,
        &RLG.lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_LightRotate(unsigned int light, Vector3 axis, float degrees)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_LightRotate' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];
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

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].direction,
        &RLG.lights[light].direction, SHADER_UNIFORM_VEC3);
}

void RLG_SetLightDirection(unsigned int light, float x, float y, float z)
{
    RLG_SetLightDirectionV(light, (Vector3) { x, y, z });
}

void RLG_SetLightDirectionV(unsigned int light, Vector3 direction)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightDirection' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].direction = direction;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].direction,
        &RLG.lights[light].direction, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetLightDirection(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightDirection' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return (Vector3) { 0 };
    }

    return RLG.lights[light].direction;
}

void RLG_SetLightTarget(unsigned int light, float x, float y, float z)
{
    RLG_SetLightTargetV(light, (Vector3) { x, y, z });
}

void RLG_SetLightTargetV(unsigned int light, Vector3 targetPosition)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightTarget' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].direction = Vector3Normalize(Vector3Subtract(
        targetPosition, RLG.lights[light].position));

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].direction,
        &RLG.lights[light].direction, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetLightTarget(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightTarget' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return (Vector3) { 0 };
    }

    return Vector3Add(
        RLG.lights[light].position,
        RLG.lights[light].direction);
}

void RLG_SetLightDiffuse(unsigned int light, float r, float g, float b)
{
    RLG_SetLightDiffuseV(light, (Vector3) { r, g, b });
}

void RLG_SetLightDiffuseV(unsigned int light, Vector3 color)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightDiffuse' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].diffuse = color;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].diffuse,
        &RLG.lights[light].diffuse, SHADER_UNIFORM_VEC3);
}

void RLG_SetLightDiffuseC(unsigned int light, Color color)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightDiffuseC' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].diffuse = (Vector3) {
        (float)color.r*(1.0f/255),
        (float)color.g*(1.0f/255),
        (float)color.b*(1.0f/255)
    };

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].diffuse,
        &RLG.lights[light].diffuse, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetLightDiffuse(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightDiffuse' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return (Vector3) { 0 };
    }

    return RLG.lights[light].diffuse;
}

Color RLG_GetLightDiffuseC(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightDiffuseC' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return BLANK;
    }

    return (Color) {
        (unsigned char)(255*RLG.lights[light].diffuse.x),
        (unsigned char)(255*RLG.lights[light].diffuse.y),
        (unsigned char)(255*RLG.lights[light].diffuse.z),
        255
    };
}

void RLG_SetLightSpecular(unsigned int light, float r, float g, float b)
{
    RLG_SetLightSpecularV(light, (Vector3) { r, g, b });
}

void RLG_SetLightSpecularV(unsigned int light, Vector3 color)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightSpecular' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].specular = color;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].specular,
        &RLG.lights[light].specular, SHADER_UNIFORM_VEC3);
}

void RLG_SetLightSpecularC(unsigned int light, Color color)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightSpecularC' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].specular = (Vector3) {
        (float)color.r*(1.0f/255),
        (float)color.g*(1.0f/255),
        (float)color.b*(1.0f/255)
    };

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].specular,
        &RLG.lights[light].specular, SHADER_UNIFORM_VEC3);
}

Vector3 RLG_GetLightSpecular(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightSpecular' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return (Vector3) { 0 };
    }

    return RLG.lights[light].specular;
}

Color RLG_GetLightSpecularC(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightSpecularC' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return BLANK;
    }

    return (Color) {
        (unsigned char)(255*RLG.lights[light].diffuse.x),
        (unsigned char)(255*RLG.lights[light].diffuse.y),
        (unsigned char)(255*RLG.lights[light].diffuse.z),
        255
    };
}

void RLG_SetLightInnerCutOff(unsigned int light, float degrees)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightInnerCutOff' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].innerCutOff = cosf(degrees*DEG2RAD);
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].innerCutOff,
        &RLG.lights[light].innerCutOff, SHADER_UNIFORM_FLOAT);
}

float RLG_GetLightInnerCutoff(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightInnerCutoff' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return 0;
    }

    return RLG.lights[light].innerCutOff;
}

void RLG_SetLightOuterCutOff(unsigned int light, float degrees)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightOuterCutOff' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].outerCutOff = cosf(degrees*DEG2RAD);
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].outerCutOff,
        &RLG.lights[light].outerCutOff, SHADER_UNIFORM_FLOAT);
}

float RLG_GetLightOuterCutoff(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightOuterCutoff' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return 0;
    }

    return RLG.lights[light].outerCutOff;
}

void RLG_SetLightAttenuation(unsigned int light, float constant, float linear, float quadratic)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightAttenuation' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].constant = constant;
    RLG.lights[light].linear = linear;
    RLG.lights[light].quadratic = quadratic;

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].constant,
        &RLG.lights[light].constant, SHADER_UNIFORM_FLOAT);

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].linear,
        &RLG.lights[light].linear, SHADER_UNIFORM_FLOAT);

    SetShaderValue(RLG.lightShader, RLG.locsLights[light].quadratic,
        &RLG.lights[light].quadratic, SHADER_UNIFORM_FLOAT);
}

void RLG_GetLightAttenuation(unsigned int light, float* constant, float* linear, float* quadratic)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_GetLightAttenuation' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    if (constant) *constant = RLG.lights[light].constant;
    if (linear) *linear = RLG.lights[light].linear;
    if (quadratic) *quadratic = RLG.lights[light].linear;
}

void RLG_SetLightAttenuationQuadratic(unsigned int light, float quadratic)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightAttenuationQuadratic' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].quadratic = quadratic;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].quadratic,
        &RLG.lights[light].quadratic, SHADER_UNIFORM_FLOAT);
}

void RLG_SetLightAttenuationConstant(unsigned int light, float constant)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightAttenuationConstant' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].constant = constant;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].constant,
        &RLG.lights[light].constant, SHADER_UNIFORM_FLOAT);
}

void RLG_SetLightAttenuationLinear(unsigned int light, float linear)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightAttenuationLinear' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].linear = linear;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].linear,
        &RLG.lights[light].linear, SHADER_UNIFORM_FLOAT);
}

void RLG_EnableLightShadow(unsigned int light, int shadowMapResolution)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_EnableLightShadow' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];

    if (l->type == RLG_OMNILIGHT)
    {
        TraceLog(LOG_WARNING, "The light [ID %i] is of type 'RLG_OMNILIGHT', shadow support for omnilights is not yet implemented, so please specify the light direction.", light, RLG.lightCount);
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
        SetShaderValue(RLG.lightShader, RLG.locsLights[light].shadowMapTxlSz,
            &texelSize, SHADER_UNIFORM_FLOAT);

        // NOTE: This is a rough approximation, other factors may affect this variable.
        //       A better approach would be to calculate the bias in the shader,
        //       taking into account factors such as the distance between the
        //       light and the fragment position.
        l->depthBias = 0.1f*shadowMapResolution*tan(acosf(l->outerCutOff));
        SetShaderValue(RLG.lightShader, RLG.locsLights[light].depthBias,
            &l->depthBias, SHADER_UNIFORM_FLOAT);
    }

    l->shadow = 1;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].shadow,
        &RLG.lights[light].shadow, SHADER_UNIFORM_INT);
}

void RLG_DisableLightShadow(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_DisableLightShadow' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].shadow = 0;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].shadow,
        &RLG.lights[light].shadow, SHADER_UNIFORM_INT);
}

bool RLG_IsLightShadowEnabled(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_IsLightShadowEnabled' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return false;
    }

    return RLG.lights[light].shadow;
}

void RLG_SetLightShadowBias(unsigned int light, float value)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightShadowBias' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    RLG.lights[light].depthBias = value;
    SetShaderValue(RLG.lightShader, RLG.locsLights[light].depthBias,
        &value, SHADER_UNIFORM_FLOAT);
}

float RLG_GetLightShadowBias(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_SetLightShadowBias' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return 0;
    }

    return RLG.lights[light].depthBias;
}

// TODO: Review the operation for the CSM
void RLG_BeginShadowCast(unsigned int light)
{
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_BeginShadowCast' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    struct RLG_Light *l = &RLG.lights[light];

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

    Matrix matView = MatrixLookAt(l->position, Vector3Add(l->position, l->direction), (Vector3){ 0, 1, 0 });
    rlMultMatrixf(MatrixToFloat(matView));

    rlEnableDepthTest();
    rlDisableColorBlend();

    Matrix viewProj = MatrixMultiply(matView, rlGetMatrixProjection());
    SetShaderValueMatrix(RLG.lightShader, RLG.locsLights[light].vpMatrix, viewProj);
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
    if (light >= RLG.lightCount)
    {
        TraceLog(LOG_ERROR, "Light [ID %i] specified to 'RLG_DrawShadowMap' exceeds allocated number [MAX %i]", light, RLG.lightCount);
        return;
    }

    if (near != RLG.shadowMapShaderData.near)
    {
        RLG.shadowMapShaderData.near = near;
        SetShaderValue(RLG.shadowMapShader, RLG.shadowMapShaderData.locNear,
            &RLG.shadowMapShaderData.near, SHADER_UNIFORM_FLOAT);
    }

    if (far != RLG.shadowMapShaderData.far)
    {
        RLG.shadowMapShaderData.far = far;
        SetShaderValue(RLG.shadowMapShader, RLG.shadowMapShaderData.locFar,
            &RLG.shadowMapShaderData.far, SHADER_UNIFORM_FLOAT);
    }

    BeginShaderMode(RLG.shadowMapShader);
    rlBegin(RL_QUADS);

        rlSetTexture(RLG.lights[light].shadowMap.depth.id);

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
    rlEnableShader(RLG.depthShader.id);

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
        rlSetVertexAttribute(RLG.depthShader.locs[SHADER_LOC_VERTEX_POSITION], 3, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(RLG.depthShader.locs[SHADER_LOC_VERTEX_POSITION]);

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
        rlSetUniformMatrix(RLG.depthShader.locs[SHADER_LOC_MATRIX_MVP], matModelViewProjection);

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
    rlEnableShader(RLG.lightShader.id);

    // Send required data to shader (matrices, values)
    //-----------------------------------------------------
    // Upload to shader globalLight.colDiffuse
    if (RLG.lightShader.locs[SHADER_LOC_COLOR_DIFFUSE] != -1)
    {
        float values[4] = {
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.r/255.0f,
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.g/255.0f,
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.b/255.0f,
            (float)material.maps[MATERIAL_MAP_DIFFUSE].color.a/255.0f
        };

        rlSetUniform(RLG.lightShader.locs[SHADER_LOC_COLOR_DIFFUSE], values, SHADER_UNIFORM_VEC4, 1);
    }

    // Upload to shader globalLight.colSpecular (if location available)
    if (RLG.lightShader.locs[SHADER_LOC_COLOR_SPECULAR] != -1)
    {
        float values[4] = {
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.r/255.0f,
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.g/255.0f,
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.b/255.0f,
            (float)material.maps[MATERIAL_MAP_SPECULAR].color.a/255.0f
        };

        rlSetUniform(RLG.lightShader.locs[SHADER_LOC_COLOR_SPECULAR], values, SHADER_UNIFORM_VEC4, 1);
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
    if (RLG.lightShader.locs[SHADER_LOC_MATRIX_VIEW] != -1) rlSetUniformMatrix(RLG.lightShader.locs[SHADER_LOC_MATRIX_VIEW], matView);
    if (RLG.lightShader.locs[SHADER_LOC_MATRIX_PROJECTION] != -1) rlSetUniformMatrix(RLG.lightShader.locs[SHADER_LOC_MATRIX_PROJECTION], matProjection);

    // Model transformation matrix is sent to shader uniform location: SHADER_LOC_MATRIX_MODEL
    if (RLG.lightShader.locs[SHADER_LOC_MATRIX_MODEL] != -1) rlSetUniformMatrix(RLG.lightShader.locs[SHADER_LOC_MATRIX_MODEL], transform);

    // Accumulate several model transformations:
    //    transform: model transformation provided (includes DrawModel() params combined with model.transform)
    //    rlGetMatrixTransform(): rlgl internal transform matrix due to push/pop matrix stack
    matModel = MatrixMultiply(transform, rlGetMatrixTransform());

    // Get model-view matrix
    matModelView = MatrixMultiply(matModel, matView);

    // Upload model normal matrix (if locations available)
    if (RLG.lightShader.locs[SHADER_LOC_MATRIX_NORMAL] != -1) rlSetUniformMatrix(RLG.lightShader.locs[SHADER_LOC_MATRIX_NORMAL], MatrixTranspose(MatrixInvert(matModel)));
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

            rlSetUniform(RLG.lightShader.locs[SHADER_LOC_MAP_DIFFUSE + i], &i, SHADER_UNIFORM_INT, 1);
        }
    }

    // Bind depth textures for shadow mapping
    for (int i = 0; i < RLG.lightCount; i++)
    {
        if (RLG.lights[i].shadow)
        {
            int j = 11 + i;
            rlActiveTextureSlot(j);
            rlEnableTexture(RLG.lights[i].shadowMap.depth.id);
            rlSetUniform(RLG.locsLights[i].shadowMap, &j, SHADER_UNIFORM_INT, 1);
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
        rlSetVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_POSITION], 3, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_POSITION]);

        // Bind mesh VBO data: vertex texcoords (shader-location = 1)
        rlEnableVertexBuffer(mesh.vboId[1]);
        rlSetVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD01], 2, RL_FLOAT, 0, 0, 0);
        rlEnableVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD01]);

        if (RLG.lightShader.locs[SHADER_LOC_VERTEX_NORMAL] != -1)
        {
            // Bind mesh VBO data: vertex normals (shader-location = 2)
            rlEnableVertexBuffer(mesh.vboId[2]);
            rlSetVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_NORMAL], 3, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_NORMAL]);
        }

        // Bind mesh VBO data: vertex colors (shader-location = 3, if available)
        if (RLG.lightShader.locs[SHADER_LOC_VERTEX_COLOR] != -1)
        {
            if (mesh.vboId[3] != 0)
            {
                rlEnableVertexBuffer(mesh.vboId[3]);
                rlSetVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_COLOR], 4, RL_UNSIGNED_BYTE, 1, 0, 0);
                rlEnableVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_COLOR]);
            }
            else
            {
                // Set default value for defined vertex attribute in shader but not provided by mesh
                // WARNING: It could result in GPU undefined behaviour
                float value[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
                rlSetVertexAttributeDefault(RLG.lightShader.locs[SHADER_LOC_VERTEX_COLOR], value, SHADER_ATTRIB_VEC4, 4);
                rlDisableVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_COLOR]);
            }
        }

        // Bind mesh VBO data: vertex tangents (shader-location = 4, if available)
        if (RLG.lightShader.locs[SHADER_LOC_VERTEX_TANGENT] != -1)
        {
            rlEnableVertexBuffer(mesh.vboId[4]);
            rlSetVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_TANGENT], 4, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_TANGENT]);
        }

        // Bind mesh VBO data: vertex texcoords2 (shader-location = 5, if available)
        if (RLG.lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD02] != -1)
        {
            rlEnableVertexBuffer(mesh.vboId[5]);
            rlSetVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD02], 2, RL_FLOAT, 0, 0, 0);
            rlEnableVertexAttribute(RLG.lightShader.locs[SHADER_LOC_VERTEX_TEXCOORD02]);
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
        rlSetUniformMatrix(RLG.lightShader.locs[SHADER_LOC_MATRIX_MVP], matModelViewProjection);

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
    for (int i = 0; i < RLG.lightCount; i++)
    {
        if (RLG.lights[i].shadow)
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