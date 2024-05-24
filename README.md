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
