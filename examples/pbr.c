#include "raylib.h"
#include <raymath.h>

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

int main(void)
{
    InitWindow(800, 600, "PBR preview");

    Camera camera = {
        .position = (Vector3) { 0.0f, 0.0f, 4.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f
    };

    RLG_Context rlgCtx = RLG_CreateContext(1);
    RLG_SetContext(rlgCtx);

    RLG_UseMap(MATERIAL_MAP_NORMAL, true);
    RLG_UseMap(MATERIAL_MAP_METALNESS, true);
    RLG_UseMap(MATERIAL_MAP_ROUGHNESS, true);
    RLG_UseMap(MATERIAL_MAP_OCCLUSION, true);

    RLG_UseLight(0, true);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightXYZ(0, RLG_LIGHT_POSITION, 0, 0, 4);

    Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 32, 64));
    GenMeshTangents(&sphere.meshes[0]);

    sphere.materials[0].maps[MATERIAL_MAP_METALNESS].value = 1.0f;
    sphere.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 1.0f;

    sphere.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("resources/pbr/albedo.png");
    SetTextureFilter(sphere.materials[0].maps[MATERIAL_MAP_ALBEDO].texture, TEXTURE_FILTER_BILINEAR);
    GenTextureMipmaps(&sphere.materials[0].maps[MATERIAL_MAP_ALBEDO].texture);

    sphere.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/pbr/normal.png");
    SetTextureFilter(sphere.materials[0].maps[MATERIAL_MAP_NORMAL].texture, TEXTURE_FILTER_BILINEAR);
    GenTextureMipmaps(&sphere.materials[0].maps[MATERIAL_MAP_NORMAL].texture);

    sphere.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/pbr/metallic.png");
    SetTextureFilter(sphere.materials[0].maps[MATERIAL_MAP_METALNESS].texture, TEXTURE_FILTER_BILINEAR);
    GenTextureMipmaps(&sphere.materials[0].maps[MATERIAL_MAP_METALNESS].texture);

    sphere.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = LoadTexture("resources/pbr/roughness.png");
    SetTextureFilter(sphere.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture, TEXTURE_FILTER_BILINEAR);
    GenTextureMipmaps(&sphere.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture);

    sphere.materials[0].maps[MATERIAL_MAP_OCCLUSION].texture = LoadTexture("resources/pbr/ao.png");
    SetTextureFilter(sphere.materials[0].maps[MATERIAL_MAP_OCCLUSION].texture, TEXTURE_FILTER_BILINEAR);
    GenTextureMipmaps(&sphere.materials[0].maps[MATERIAL_MAP_OCCLUSION].texture);

    Texture2D preview = LoadTexture("resources/pbr/preview.png");

    float modelScale = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        RLG_SetViewPositionV(camera.position);
        RLG_SetLightVec3(0, RLG_LIGHT_POSITION, camera.position);
        RLG_SetLightTargetV(0, camera.target);

        modelScale = Clamp(modelScale + GetMouseWheelMove() * 0.1, 0.25f, 2.5f);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            // Créez des matrices de rotation pour les axes X et Y
            Matrix rotationX = MatrixRotateX((GetMouseDelta().y * 0.0025f) / modelScale);
            Matrix rotationY = MatrixRotateY((GetMouseDelta().x * 0.0025f) / modelScale);

            // Appliquez les rotations à la matrice de transformation accumulée
            sphere.transform = MatrixMultiply(sphere.transform, rotationX);
            sphere.transform = MatrixMultiply(sphere.transform, rotationY);
        }

        if (IsKeyPressed(KEY_KP_0)) RLG_UseMap(MATERIAL_MAP_ALBEDO, !RLG_IsMapUsed(MATERIAL_MAP_ALBEDO));
        if (IsKeyPressed(KEY_KP_1)) RLG_UseMap(MATERIAL_MAP_NORMAL, !RLG_IsMapUsed(MATERIAL_MAP_NORMAL));
        if (IsKeyPressed(KEY_KP_2)) RLG_UseMap(MATERIAL_MAP_METALNESS, !RLG_IsMapUsed(MATERIAL_MAP_METALNESS));
        if (IsKeyPressed(KEY_KP_3)) RLG_UseMap(MATERIAL_MAP_ROUGHNESS, !RLG_IsMapUsed(MATERIAL_MAP_ROUGHNESS));
        if (IsKeyPressed(KEY_KP_4)) RLG_UseMap(MATERIAL_MAP_OCCLUSION, !RLG_IsMapUsed(MATERIAL_MAP_OCCLUSION));

        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode3D(camera);
                RLG_DrawModel(sphere, Vector3Zero(), modelScale, WHITE);
            EndMode3D();

            DrawTextureEx(preview, (Vector2) { 800 - preview.width*0.125f, 0 }, 0, 0.125f, WHITE);

            DrawText(TextFormat("[KP_0] - ALBEDO: %s", RLG_IsMapUsed(MATERIAL_MAP_ALBEDO) ? "ON" : "OFF"), 10, 10, 20, LIME);
            DrawText(TextFormat("[KP_1] - NORMAL: %s", RLG_IsMapUsed(MATERIAL_MAP_NORMAL) ? "ON" : "OFF"), 10, 40, 20, LIME);
            DrawText(TextFormat("[KP_2] - METALNESS: %s", RLG_IsMapUsed(MATERIAL_MAP_METALNESS) ? "ON" : "OFF"), 10, 70, 20, LIME);
            DrawText(TextFormat("[KP_3] - ROUGHNESS: %s", RLG_IsMapUsed(MATERIAL_MAP_ROUGHNESS) ? "ON" : "OFF"), 10, 100, 20, LIME);
            DrawText(TextFormat("[KP_4] - OCCLUSION: %s", RLG_IsMapUsed(MATERIAL_MAP_OCCLUSION) ? "ON" : "OFF"), 10, 130, 20, LIME);

        EndDrawing();
    }

    UnloadTexture(preview);

    UnloadTexture(sphere.materials[0].maps[MATERIAL_MAP_ALBEDO].texture);
    UnloadTexture(sphere.materials[0].maps[MATERIAL_MAP_NORMAL].texture);
    UnloadTexture(sphere.materials[0].maps[MATERIAL_MAP_METALNESS].texture);
    UnloadTexture(sphere.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture);
    UnloadTexture(sphere.materials[0].maps[MATERIAL_MAP_OCCLUSION].texture);

    UnloadModel(sphere);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}
