#include "raylib.h"

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

int main(void)
{
    InitWindow(800, 600, "basic lighting");

    Camera camera = {
        .position = (Vector3) { 2.0f, 2.0f, 2.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f
    };

    RLG_Context rlgCtx = RLG_CreateContext(1);
    RLG_SetContext(rlgCtx);

    RLG_SetMaterialValue(RLG_MAT_SPECULAR_TINT, 0.5f);

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

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}
