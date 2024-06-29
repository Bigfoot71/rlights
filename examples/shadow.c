#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

static Model cube = (Model) { 0 };
static Model plane = (Model) { 0 };

void cast(Shader shader)
{
    for (int x = -1; x <= 1; x++)
    {
        for (int z = -1; z <= 1; z++)
        {
            RLG_CastModel(shader, cube, (Vector3) { x*5, 0.0f, z*5 }, 1);
        }
    }
}

void draw(void)
{
    RLG_DrawModel(plane, (Vector3) { 0, -0.5, 0 }, 1, WHITE);

    for (int x = -1; x <= 1; x++)
    {
        for (int z = -1; z <= 1; z++)
        {
            RLG_DrawModel(cube, (Vector3) { x*5, 0.0f, z*5 }, 1, WHITE);
        }
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

    RLG_SetViewPositionV(camera.position);

    for (int i = 0; i < RLG_GetLightcount(); i++)
    {
        RLG_UseLight(i, true);
        RLG_SetLightType(i, RLG_OMNILIGHT);

        RLG_EnableShadow(i, 1024);
        RLG_SetLightXYZ(i, RLG_LIGHT_COLOR, 1 - i, 0.0f, i);

        int s = i == 0 ? 1 : -1;
        RLG_SetLightXYZ(i, RLG_LIGHT_POSITION, s*5, 2.5f, s*5);
        RLG_SetLightTarget(i, 0, 0, 0);

        RLG_SetLightValue(i, RLG_LIGHT_INNER_CUTOFF, 17.5f);
        RLG_SetLightValue(i, RLG_LIGHT_OUTER_CUTOFF, 22.5f); 
    }

    cube = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    cube.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.9f;
    cube.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.1f;

    plane = LoadModelFromMesh(GenMeshPlane(1000, 1000, 1, 1));
    cube.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.5f;
    cube.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.5f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        BeginDrawing();

            ClearBackground(BLACK);

            for (int i = 0; i < RLG_GetLightcount(); i++)
            {
                int s = i == 0 ? 1 : -1;
                RLG_SetLightXYZ(i, RLG_LIGHT_POSITION, s*5*cosf(GetTime()*(i+1)*0.5f), 2.5f, s*5*sinf(GetTime()*(i+1)*0.5f));
                RLG_SetLightTarget(i, 0, 0, 0);

                RLG_UpdateShadowMap(i, cast);
            }

            BeginMode3D(camera);
                for (int i = 0; i < RLG_GetLightcount(); i++)
                {
                    DrawSphere(RLG_GetLightVec3(i, RLG_LIGHT_POSITION),
                        0.1f, RLG_GetLightColor(i));
                }
                draw();
            EndMode3D();

        EndDrawing();
    }

    UnloadModel(cube);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}
