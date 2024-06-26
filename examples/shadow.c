#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

static Model cube = (Model) { 0 };
static Model plane = (Model) { 0 };

void draw(bool cast)
{
    if (cast)
    {
        // NOTE: You are not required to use RLG_CastModel
        //       to record their depth, but its use
        //       is simpler and more optimized.
        RLG_CastModel(plane, (Vector3) { 0, -0.5, 0 }, 1);
        RLG_CastModel(cube, Vector3Zero(), 1);
    }
    else
    {
        RLG_DrawModel(plane, (Vector3) { 0, -0.5, 0 }, 1, WHITE);
        RLG_DrawModel(cube, Vector3Zero(), 1, WHITE);
    }
}

int main(void)
{
    InitWindow(800, 600, "shadow");

    Camera camera = {
        .position = (Vector3) { 8.0f, 8.0f, 8.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f
    };

    RLG_Context rlgCtx = RLG_CreateContext(2);
    RLG_SetContext(rlgCtx);

    RLG_SetMaterialValue(RLG_MAT_SPECULAR_TINT, 0.5f);
    RLG_SetViewPositionV(camera.position);

    for (int i = 0; i < RLG_GetLightcount(); i++)
    {
        RLG_SetLight(i, true);
        RLG_SetLightType(i, RLG_SPOTLIGHT);

        RLG_EnableLightShadow(i, 1024);
        RLG_SetLightXYZ(i, RLG_LIGHT_DIFFUSE, 1 - i, 0.0f, i);

        int s = i == 0 ? 1 : -1;
        RLG_SetLightXYZ(i, RLG_LIGHT_POSITION, s*5, 2.5f, s*5);
        RLG_SetLightTarget(i, 0, 0, 0);

        RLG_SetLightValue(i, RLG_LIGHT_INNER_CUTOFF, 17.5f);
        RLG_SetLightValue(i, RLG_LIGHT_OUTER_CUTOFF, 22.5f); 
    }

    cube = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    plane = LoadModelFromMesh(GenMeshPlane(10, 10, 1, 1));

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);

            for (int i = 0; i < RLG_GetLightcount(); i++)
            {
                int s = i == 0 ? 1 : -1;
                RLG_SetLightXYZ(i, RLG_LIGHT_POSITION, s*5*cosf(GetTime()*(i+1)*0.5f), 2.5f, s*5*sinf(GetTime()*(i+1)*0.5f));
                RLG_SetLightTarget(i, 0, 0, 0);

                RLG_BeginShadowCast(i);
                    RLG_ClearShadowMap();
                    draw(true);
                RLG_EndShadowCast();

                RLG_DrawShadowMap(i, i*100, 0, 100, 100);
                DrawRectangleLines(i*100, 0, 100, 100, RED);
            }

            BeginMode3D(camera);
                for (int i = 0; i < RLG_GetLightcount(); i++)
                {
                    DrawSphere(RLG_GetLightVec3(i, RLG_LIGHT_POSITION),
                        0.1f, RLG_GetLightColor(i, RLG_LIGHT_DIFFUSE));
                }
                draw(false);
            EndMode3D();

        EndDrawing();
    }

    UnloadModel(cube);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}
