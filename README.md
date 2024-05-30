# rlights.h

`rlights.h` is a single-header library that provides a simple implementation of a lighting system for [raylib](https://www.raylib.com/).

## Features
- **Directional Lights**: Simulate sunlight or other distant light sources.
- **Omni-Directional Lights**: Point lights that emit in all directions.
- **Spotlights**: Lights with a specific direction and cone of influence.
- **Normal Mapping**: Adds depth and detail to surfaces without increasing polygon count.
- **Shadow Mapping**: Allows the rendering of cast shadows in your scenes.
- **Integrated Shaders**: The header already contains all the shaders, but you can also use your own shaders.

## Usage
Using `rlights.h` is straightforward. Include the header file in your project with the following setup:

```c
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
```

### Example
Here's a basic example demonstrating how to set up and use `rlights.h` with raylib:

```c
#include "raylib.h"

#define RLIGHTS_IMPLEMENTATION
#define GLSL_VERSION 330        ///< or 120/130/etc.. 100 is default if 'PLATFORM_DESKTOP' is not defined
#include "rlights.h"

int main(void)
{
    InitWindow(800, 600, "basic example");

    Camera camera = {
        .position = (Vector3) { 2.0f, 2.0f, 2.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f
    };

    RLG_Init(1);

    RLG_EnableLight(0);
    RLG_SetLightPosition(0, 2, 2, 2);
    RLG_SetLightType(0, RLG_OMNILIGHT);

    Model cube = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    cube.materials[0].shader = *RLG_GetShader();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        RLG_SetViewPositionV(camera.position);

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
                DrawModel(cube, Vector3Zero(), 1, WHITE);
            EndMode3D();

        EndDrawing();
    }

    UnloadModel(cube);

    RLG_Close();
    CloseWindow();

    return 0;
}
```

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Cheatsheet

```c
void RLG_Init(unsigned int lightCount);
void RLG_Close(void);

void RLG_SetLightingShaderCode(const char *vsCode, const char *fsCode);
void RLG_SetDepthShaderCode(const char *vsCode, const char *fsCode);
void RLG_SetShadowMapShaderCode(const char *vsCode, const char *fsCode);

const Shader* RLG_GetLightShader(void);
const Shader* RLG_GetDepthShader(void);

void RLG_SetViewPosition(float x, float y, float z);
void RLG_SetViewPositionV(Vector3 position);
Vector3 RLG_GetViewPosition(void);

void RLG_EnableSpecularMap(void);
void RLG_DisableSpecularMap(void);
bool RLG_IsSpecularMapEnabled(void);

void RLG_EnableNormalMap(void);
void RLG_DisableNormalMap(void);
bool RLG_IsNormalMapEnabled(void);

void RLG_SetShininess(float value);
float RLG_GetShininess(void);

void RLG_SetSpecular(float r, float g, float b);
void RLG_SetSpecularV(Vector3 color);
void RLG_SetSpecularC(Color color);
Vector3 RLG_GetSpecular(void);
Color RLG_GetSpecularC(void);

void RLG_SetAmbient(float r, float g, float b);
void RLG_SetAmbientV(Vector3 color);
void RLG_SetAmbientC(Color color);
Vector3 RLG_GetAmbient(void);
Color RLG_GetAmbientC(void);

unsigned int RLG_GetLightcount(void);

void RLG_ToggleLight(unsigned int light);
void RLG_EnableLight(unsigned int light);
void RLG_DisableLight(unsigned int light);
bool RLG_IsLightEnabled(unsigned int light);

void RLG_SetLightType(unsigned int light, RLG_LightType type);
RLG_LightType RLG_GetLightType(unsigned int light);

void RLG_LightTranslate(unsigned int light, float x, float y, float z);
void RLG_LightTranslateV(unsigned int light, Vector3 v);

void RLG_SetLightPosition(unsigned int light, float x, float y, float z);
void RLG_SetLightPositionV(unsigned int light, Vector3 position);
Vector3 RLG_GetLightPosition(unsigned int light);

void RLG_LightRotateX(unsigned int light, float degrees);
void RLG_LightRotateY(unsigned int light, float degrees);
void RLG_LightRotateZ(unsigned int light, float degrees);
void RLG_LightRotate(unsigned int light, Vector3 axis, float degrees);

void RLG_SetLightDirection(unsigned int light, float x, float y, float z);
void RLG_SetLightDirectionV(unsigned int light, Vector3 direction);
Vector3 RLG_GetLightDirection(unsigned int light);

void RLG_SetLightTarget(unsigned int light, float x, float y, float z);
void RLG_SetLightTargetV(unsigned int light, Vector3 targetPosition);
Vector3 RLG_GetLightTarget(unsigned int light);

void RLG_SetLightDiffuse(unsigned int light, float r, float g, float b);
void RLG_SetLightDiffuseV(unsigned int light, Vector3 color);
void RLG_SetLightDiffuseC(unsigned int light, Color color);
Vector3 RLG_GetLightDiffuse(unsigned int light);
Color RLG_GetLightDiffuseC(unsigned int light);

void RLG_SetLightSpecular(unsigned int light, float r, float g, float b);
void RLG_SetLightSpecularV(unsigned int light, Vector3 color);
void RLG_SetLightSpecularC(unsigned int light, Color color);
Vector3 RLG_GetLightSpecular(unsigned int light);
Color RLG_GetLightSpecularC(unsigned int light);

void RLG_SetLightInnerCutOff(unsigned int light, float degrees);
float RLG_GetLightInnerCutoff(unsigned int light);

void RLG_SetLightOuterCutOff(unsigned int light, float degrees);
float RLG_GetLightOuterCutoff(unsigned int light);

void RLG_SetLightAttenuation(unsigned int light, float constant, float linear, float quadratic);
void RLG_GetLightAttenuation(unsigned int light, float* constant, float* linear, float* quadratic);

void RLG_SetLightAttenuationQuadratic(unsigned int light, float quadratic);
void RLG_SetLightAttenuationConstant(unsigned int light, float constant);
void RLG_SetLightAttenuationLinear(unsigned int light, float linear);

void RLG_EnableLightShadow(unsigned int light, int shadowMapResolution);
void RLG_DisableLightShadow(unsigned int light);
bool RLG_IsLightShadowEnabled(unsigned int light);

void RLG_SetLightShadowBias(unsigned int light, float value);
float RLG_GetLightShadowBias(unsigned int light);

void RLG_BeginShadowCast(unsigned int light);
void RLG_EndShadowCast(void);

void RLG_ClearShadowMap(void);

void RLG_DrawShadowMap(unsigned int light, int x, int y, int w, int h);
void RLG_DrawShadowMapEx(unsigned int light, int x, int y, int w, int h, float near, float far);

void RLG_CastMesh(Mesh mesh, Material material, Matrix transform);
void RLG_CastModel(Model model, Vector3 position, float scale);
void RLG_CastModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale);

void RLG_DrawMesh(Mesh mesh, Material material, Matrix transform);
void RLG_DrawModel(Model model, Vector3 position, float scale, Color tint);
void RLG_DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
```