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

    RLG_SetMap(RLG_MAP_NORMAL, true);
    RLG_SetMap(RLG_MAP_METALNESS, true);
    RLG_SetMap(RLG_MAP_ROUGHNESS, true);
    RLG_SetMap(RLG_MAP_OCCLUSION, true);

    RLG_SetMaterialValue(RLG_MAT_METALNESS, 1.0f);
    RLG_SetMaterialValue(RLG_MAT_ROUGHNESS, 1.0f);

    RLG_SetLight(0, true);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightXYZ(0, RLG_LIGHT_POSITION, 0, 0, 4);

    Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 32, 64));
    GenMeshTangents(&sphere.meshes[0]);

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

        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode3D(camera);
                RLG_DrawModel(sphere, Vector3Zero(), modelScale, WHITE);
            EndMode3D();

            DrawTextureEx(preview, Vector2Zero(), 0, 0.125, WHITE);

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
