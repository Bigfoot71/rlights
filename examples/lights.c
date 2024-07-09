#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

void Init_OmniLight(unsigned int light, Vector3 position, Color color)
{
    RLG_UseLight(light, true);
    RLG_SetLightColor(light, color);
    RLG_SetLightType(light, RLG_OMNILIGHT);
    RLG_SetLightVec3(light, RLG_LIGHT_POSITION, position);
}

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(800, 600, "multiple lights");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 4.0f, 6.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Init light system
    RLG_Context rlgCtx = RLG_CreateContext(4);
    RLG_SetContext(rlgCtx);

    RLG_UseDefaultMap(MATERIAL_MAP_METALNESS, true);
    RLG_UseDefaultMap(MATERIAL_MAP_ROUGHNESS, true);

    Init_OmniLight(0, (Vector3) { -2, 1, -2 }, YELLOW);
    Init_OmniLight(1, (Vector3) { 2, 1, 2 }, RED);
    Init_OmniLight(2, (Vector3) { -2, 1, 2 }, GREEN);
    Init_OmniLight(3, (Vector3) { 2, 1, -2 }, BLUE);

    // Generate meshes/models
    Model cube = LoadModelFromMesh(GenMeshCube(2.0f, 4.0f, 2.0f));
    Model plane = LoadModelFromMesh(GenMeshPlane(10.0f, 10.0f, 1, 1));

    // Main game loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        UpdateCamera(&camera, CAMERA_ORBITAL);
        RLG_SetViewPositionV(camera.position);

        // Check key inputs to config material values
        int metalness = IsKeyPressed(KEY_RIGHT) - IsKeyPressed(KEY_LEFT);
        if (metalness)
        {
            MaterialMap map = RLG_GetDefaultMap(MATERIAL_MAP_METALNESS);
            map.value = Clamp(map.value + metalness*0.05f, 0.0f, 1.0f);
            RLG_SetDefaultMap(MATERIAL_MAP_METALNESS, map);
        }

        float roughness = IsKeyPressed(KEY_UP) - IsKeyPressed(KEY_DOWN);
        if (roughness)
        {
            MaterialMap map = RLG_GetDefaultMap(MATERIAL_MAP_ROUGHNESS);
            map.value = Clamp(map.value + roughness*0.05f, 0.0f, 1.0f);
            RLG_SetDefaultMap(MATERIAL_MAP_ROUGHNESS, map);
        }

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) RLG_ToggleLight(0);
        if (IsKeyPressed(KEY_R)) RLG_ToggleLight(1);
        if (IsKeyPressed(KEY_G)) RLG_ToggleLight(2);
        if (IsKeyPressed(KEY_B)) RLG_ToggleLight(3);

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

                RLG_DrawModel(plane, Vector3Zero(), 1.0f, WHITE);
                RLG_DrawModel(cube, Vector3Zero(), 1.0f, WHITE);

                // Draw spheres to show where the lights are
                for (int i = 0; i < RLG_GetLightcount(); i++)
                {
                    if (RLG_IsLightUsed(i))
                    {
                        DrawSphereEx(RLG_GetLightVec3(i, RLG_LIGHT_POSITION),
                            0.2f, 8, 8, RLG_GetLightColor(i));
                    }
                    else
                    {
                        DrawSphereWires(RLG_GetLightVec3(i, RLG_LIGHT_POSITION),
                            0.2f, 8, 8, ColorAlpha(RLG_GetLightColor(i), 0.3f));
                    }
                }

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText(TextFormat("[AL/AR] Metalness: %.2f", RLG_GetDefaultMap(MATERIAL_MAP_METALNESS).value), 10, 10, 20, WHITE);
            DrawText(TextFormat("[AU/AD] Roughness: %.2f", RLG_GetDefaultMap(MATERIAL_MAP_ROUGHNESS).value), 10, 40, 20, WHITE);
            DrawText("Use keys [Y][R][G][B] to toggle lights", 420, 10, 20, WHITE);
            DrawFPS(10, 570);

        EndDrawing();
    }

    UnloadModel(cube);
    UnloadModel(plane);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}