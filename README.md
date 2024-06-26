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

    RLG_Context rlgCtx = RLG_CreateContext(1);
    RLG_SetContext(rlgCtx);

    RLG_SetMaterialValue(RLG_MAT_SPECULAR_TINT, 0.5f);

    RLG_SetLight(0, true);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightXYZ(0, RLG_LIGHT_POSITION, 2, 2, 2);
    RLG_SetLightXYZ(0, RLG_LIGHT_DIFFUSE, 0.5f, 0.0, 1.0);

    Model cube = LoadModelFromMesh(GenMeshCube(1, 1, 1));

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        RLG_SetViewPositionV(camera.position);

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
                RLG_DrawModel(cube, Vector3Zero(), 1, WHITE);
            EndMode3D();

        EndDrawing();
    }

    UnloadModel(cube);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}
```

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Cheatsheet

```c
/* Context Management */

RLG_Context RLG_CreateContext(unsigned int lightCount);
void RLG_DestroyContext(RLG_Context ctx);

void RLG_SetContext(RLG_Context ctx);
RLG_Context RLG_GetContext(void);

void RLG_SetCustomShaderCode(RLG_Shader shaderType, const char *vsCode, const char *fsCode);

const Shader* RLG_GetShader(RLG_Shader shaderType);

/* Global Variables Management */

void RLG_SetViewPosition(float x, float y, float z);
void RLG_SetViewPositionV(Vector3 position);
Vector3 RLG_GetViewPosition(void);

/* Materials Management */

void RLG_SetMap(RLG_MaterialMap map, bool active);
bool RLG_IsMapEnabled(RLG_MaterialMap map);

void RLG_SetMaterialValue(RLG_MaterialProperty property, float value);
void RLG_SetMaterialColor(RLG_MaterialProperty property, Color color);
float RLG_GetMaterialValue(RLG_MaterialProperty property);
Color RLG_GetMaterialColor(RLG_MaterialProperty property);

/* Lighting Management */

unsigned int RLG_GetLightcount(void);

void RLG_SetLight(unsigned int light, bool active);
bool RLG_IsLightEnabled(unsigned int light);
void RLG_ToggleLight(unsigned int light);

void RLG_SetLightType(unsigned int light, RLG_LightType type);
RLG_LightType RLG_GetLightType(unsigned int light);

void RLG_SetLightValue(unsigned int light, RLG_LightProperty property, float value);
void RLG_SetLightXYZ(unsigned int light, RLG_LightProperty property, float x, float y, float z);
void RLG_SetLightVec3(unsigned int light, RLG_LightProperty property, Vector3 value);
void RLG_SetLightColor(unsigned int light, RLG_LightProperty property, Color color);

float RLG_GetLightValue(unsigned int light, RLG_LightProperty property);
Vector3 RLG_GetLightVec3(unsigned int light, RLG_LightProperty property);
Color RLG_GetLightColor(unsigned int light, RLG_LightProperty property);

void RLG_LightTranslate(unsigned int light, float x, float y, float z);
void RLG_LightTranslateV(unsigned int light, Vector3 v);

void RLG_LightRotateX(unsigned int light, float degrees);
void RLG_LightRotateY(unsigned int light, float degrees);
void RLG_LightRotateZ(unsigned int light, float degrees);
void RLG_LightRotate(unsigned int light, Vector3 axis, float degrees);

void RLG_SetLightTarget(unsigned int light, float x, float y, float z);
void RLG_SetLightTargetV(unsigned int light, Vector3 targetPosition);
Vector3 RLG_GetLightTarget(unsigned int light);

/* Shadow Casting Management */

void RLG_EnableShadow(unsigned int light, int shadowMapResolution);
void RLG_DisableShadow(unsigned int light);
bool RLG_IsShadowEnabled(unsigned int light);

void RLG_SetShadowBias(unsigned int light, float value);
float RLG_GetShadowBias(unsigned int light);

void RLG_BeginShadowCast(unsigned int light);
void RLG_EndShadowCast(void);

void RLG_ClearShadowMap(void);

void RLG_DrawShadowMap(unsigned int light, int x, int y, int w, int h);
void RLG_DrawShadowMapEx(unsigned int light, int x, int y, int w, int h, float near, float far);

void RLG_CastMesh(Mesh mesh, Matrix transform);
void RLG_CastModel(Model model, Vector3 position, float scale);
void RLG_CastModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale);

/* Mesh Drawing Functions */

void RLG_DrawMesh(Mesh mesh, Material material, Matrix transform);
void RLG_DrawModel(Model model, Vector3 position, float scale, Color tint);
void RLG_DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
```