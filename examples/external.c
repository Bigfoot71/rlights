#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <string.h>

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

static void LoadShaderCode(int lightCount, char** lightVS, char** lightFS)
{
    char *tempVS = LoadFileText("../shaders/glsl100/lights.vs");
    char *tempFS = LoadFileText("../shaders/glsl100/lights.fs");

    unsigned int lenVS = strlen(tempVS);
    unsigned int lenFS = strlen(tempFS);

    *lightVS = malloc(lenVS + 1);
    *lightFS = malloc(lenFS + 1);

    sprintf(*lightVS, tempVS, lightCount);
    sprintf(*lightFS, tempFS, lightCount);

    free(tempVS);
    free(tempFS);
}

int main(void)
{
    InitWindow(800, 600, "external shader");

    Camera camera = {
        .position = (Vector3) { 2.0f, 2.0f, 2.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f
    };

    char *lightVS, *lightFS;
    const int lightCount = 1;

    LoadShaderCode(lightCount, &lightVS, &lightFS);
    RLG_SetCustomShaderCode(RLG_SHADER_LIGHT, lightVS, lightFS);

    RLG_Init(lightCount);
    RLG_SetSpecular(0.5f, 0.5f, 0.5f);

    free(lightVS);
    free(lightFS);

    RLG_EnableLight(0);
    RLG_SetLightPosition(0, 2, 2, 2);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightDiffuse(0, 0.5f, 0.0, 1.0);

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

    RLG_Close();
    CloseWindow();

    free(lightVS);
    free(lightFS);

    return 0;
}
