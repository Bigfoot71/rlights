#include "raylib.h"
#include <raymath.h>

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

int main(void)
{
    InitWindow(800, 600, "skybox example");

    Camera camera = {
        .position = (Vector3) { 0.0f, 0.0f, 8.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 60.0f
    };

    RLG_Context rlgCtx = RLG_CreateContext(1);
    RLG_SetContext(rlgCtx);

    RLG_UseMap(MATERIAL_MAP_METALNESS, true);
    RLG_UseMap(MATERIAL_MAP_ROUGHNESS, true);

    RLG_UseMap(MATERIAL_MAP_CUBEMAP, true);
    RLG_UseMap(MATERIAL_MAP_IRRADIANCE, true);

    RLG_UseLight(0, true);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightXYZ(0, RLG_LIGHT_POSITION, 0, 0, 4);

    // NOTE: HDR support only if you compiled raylib with `SUPPORT_FILEFORMAT_HDR`
    //RLG_Skybox skybox = RLG_LoadSkyboxHDR("resources/skybox.hdr", 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    RLG_Skybox skybox = RLG_LoadSkybox("resources/skybox.png");

    Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 32, 64));
    sphere.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = skybox.cubemap;
    sphere.materials[0].maps[MATERIAL_MAP_IRRADIANCE].texture = skybox.irradiance;

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        RLG_SetViewPositionV(camera.position);

        RLG_SetLightVec3(0, RLG_LIGHT_POSITION, camera.position);
        RLG_SetLightTargetV(0, camera.target);

        BeginDrawing();

            ClearBackground(BLACK);

            UpdateCamera(&camera, CAMERA_FREE);

            BeginMode3D(camera);

                RLG_DrawSkybox(skybox);

                for (int x = -5; x <= 5; x += 2)
                {
                    for (int y = -5; y <= 5; y += 2)
                    {
                        sphere.materials[0].maps[MATERIAL_MAP_METALNESS].value = (5.0f+x)/10.0f;
                        sphere.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = (5.0f+y)/10.0f;
                        RLG_DrawModel(sphere, (Vector3) { x, y, 0 }, 1.0f, WHITE);
                    }
                }

            EndMode3D();

        EndDrawing();
    }

    UnloadModel(sphere);
    RLG_UnloadSkybox(skybox);
    RLG_DestroyContext(rlgCtx);

    CloseWindow();

    return 0;
}
