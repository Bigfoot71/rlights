#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

static Model cube = (Model) { 0 };
static Model plane = (Model) { 0 };

int main(void)
{
    InitWindow(800, 600, "shadow");

    Camera camera = {
        .position = (Vector3) { 8.0f, 8.0f, 8.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f
    };

    RLG_Context rlgCtx = RLG_CreateContext(1);
    RLG_SetContext(rlgCtx);

    RLG_SetSpecular(0.5f, 0.5f, 0.5f);
    RLG_SetViewPositionV(camera.position);

    RLG_EnableLight(0);
    RLG_SetLightType(0, RLG_SPOTLIGHT);
    RLG_EnableLightShadow(0, 1024);
    RLG_SetLightPosition(0, -5, 5, -5);
    RLG_SetLightTarget(0, 0, 0, 0);
    RLG_SetLightInnerCutOff(0, 17.5f);
    RLG_SetLightOuterCutOff(0, 22.5f); 

    cube = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    plane = LoadModelFromMesh(GenMeshPlane(10, 10, 1, 1));

    bool isEmissive = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            isEmissive = !isEmissive;
        }

        BeginDrawing();

            ClearBackground(BLACK);

            RLG_BeginShadowCast(0);
                RLG_CastModel(cube, Vector3Zero(), 1);
            RLG_EndShadowCast();

            BeginMode3D(camera);

                RLG_DrawModel(plane, (Vector3) { 0, -0.5, 0 }, 1, WHITE);
    
                if (isEmissive) RLG_SetEmissiveC(RED);
                RLG_DrawModel(cube, Vector3Zero(), 1, RED);
                if (isEmissive) RLG_SetEmissiveC(BLACK);

            EndMode3D();

            DrawText("Press SPACE to toggle emission", 10, 10, 24, LIME);

        EndDrawing();
    }

    UnloadModel(cube);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}
