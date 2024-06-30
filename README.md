# rlights.h

`rlights.h` is a single-header library that provides a simple implementation of a lighting system for [raylib](https://www.raylib.com/).

## Features
- **Directional Lights**: Simulate sunlight or other distant light sources.
- **Omni-Directional Lights**: Point lights that emit in all directions.
- **Spotlights**: Lights with a specific direction and cone of influence.
- **PBR**: Supports Physically Based Rendering (PBR) including Occlusion, Roughness, and Metalness (ORM), with Burley diffuse and SchlickGGX specularity.
- **Normal Mapping**: Adds depth and detail to surfaces without increasing polygon count.
- **Parallax Mapping**: Creates an illusion of depth by displacing the texture coordinates, enhancing the surface detail with minimal geometry.
- **Shadow Mapping**: Allows the rendering of cast shadows in your scenes.
- **Integrated Shaders**: The header already contains all the shaders, but you can also use your own shaders.

## Usage
Using `rlights.h` is straightforward. Include the header file in your project with the following setup:

```c
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
```

**WARNING**: Shadow rendering for omnidirectional lights in their current implementation requires support for depth cubemaps, a feature not yet supported by raylib/rlgl. Therefore, this repository includes Glad headers, which will be used by default if you have not defined _(e.g.)_ `#define GL_HEADER "GL.h"` before including `rlights.h`. You also have the option to define an optional second header with `GL_EXT_HEADER` for necessary extensions if needed.

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

    RLG_UseLight(0, true);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightVec3(0, RLG_LIGHT_POSITION, camera.position);

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

void RLG_SetCustomShaderCode(RLG_Shader shader, const char *vsCode, const char *fsCode);
const Shader* RLG_GetShader(RLG_Shader shader);

/* Management of Specific Variables */

void RLG_SetViewPosition(float x, float y, float z);
void RLG_SetViewPositionV(Vector3 position);
Vector3 RLG_GetViewPosition(void);

void RLG_SetAmbientColor(Color color);
Color RLG_GetAmbientColor(void);

void RLG_SetParallaxLayers(int min, int max);
void RLG_GetParallaxLayers(int* min, int* max);

/* Materials Management */

void RLG_UseMap(MaterialMapIndex mapIndex, bool active);
bool RLG_IsMapUsed(MaterialMapIndex mapIndex);

void RLG_UseDefaultMap(MaterialMapIndex mapIndex, bool active);
void RLG_SetDefaultMap(MaterialMapIndex mapIndex, MaterialMap map);
MaterialMap RLG_GetDefaultMap(MaterialMapIndex mapIndex);
bool RLG_IsDefaultMapUsed(MaterialMapIndex mapIndex);

/* Lighting Management */

unsigned int RLG_GetLightcount(void);

void RLG_UseLight(unsigned int light, bool active);
bool RLG_IsLightUsed(unsigned int light);
void RLG_ToggleLight(unsigned int light);

void RLG_SetLightType(unsigned int light, RLG_LightType type);
RLG_LightType RLG_GetLightType(unsigned int light);

void RLG_SetLightValue(unsigned int light, RLG_LightProperty property, float value);
void RLG_SetLightXYZ(unsigned int light, RLG_LightProperty property, float x, float y, float z);
void RLG_SetLightVec3(unsigned int light, RLG_LightProperty property, Vector3 value);
void RLG_SetLightColor(unsigned int light, Color color);

float RLG_GetLightValue(unsigned int light, RLG_LightProperty property);
Vector3 RLG_GetLightVec3(unsigned int light, RLG_LightProperty property);
Color RLG_GetLightColor(unsigned int light);

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

void RLG_UpdateShadowMap(unsigned int light, RLG_DrawFunc drawFunc);
Texture RLG_GetShadowMap(unsigned int light);

void RLG_CastMesh(Shader shader, Mesh mesh, Matrix transform);
void RLG_CastModel(Shader shader, Model model, Vector3 position, float scale);
void RLG_CastModelEx(Shader shader, Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale);

/* Mesh/Model Drawing Functions */

void RLG_DrawMesh(Mesh mesh, Material material, Matrix transform);
void RLG_DrawModel(Model model, Vector3 position, float scale, Color tint);
void RLG_DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);

/* Fonctions de gestion des skyboxes */

RLG_Skybox RLG_LoadSkybox(const char* skyboxFileName);
RLG_Skybox RLG_LoadSkyboxHDR(const char* skyboxFileName, int size, int format);
void RLG_UnloadSkybox(RLG_Skybox skybox);
void RLG_DrawSkybox(RLG_Skybox skybox);
```