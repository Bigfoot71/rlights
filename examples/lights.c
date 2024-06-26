#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "multiple lights");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 4.0f, 6.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Init light system
    RLG_Context rlgCtx = RLG_CreateContext(4);
    RLG_SetContext(rlgCtx);

    RLG_SetMaterialValue(RLG_MAT_SPECULAR_TINT, 0.2f);

    RLG_SetLight(0, true);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightColor(0, RLG_LIGHT_DIFFUSE, YELLOW);
    RLG_SetLightXYZ(0, RLG_LIGHT_POSITION, -2, 1, -2);

    RLG_SetLight(1, true);
    RLG_SetLightType(1, RLG_OMNILIGHT);
    RLG_SetLightColor(1, RLG_LIGHT_DIFFUSE, RED);
    RLG_SetLightXYZ(1, RLG_LIGHT_POSITION, 2, 1, 2);

    RLG_SetLight(2, true);
    RLG_SetLightType(2, RLG_OMNILIGHT);
    RLG_SetLightColor(2, RLG_LIGHT_DIFFUSE, GREEN);
    RLG_SetLightXYZ(2, RLG_LIGHT_POSITION, -2, 1, 2);

    RLG_SetLight(3, true);
    RLG_SetLightType(3, RLG_OMNILIGHT);
    RLG_SetLightColor(3, RLG_LIGHT_DIFFUSE, BLUE);
    RLG_SetLightXYZ(3, RLG_LIGHT_POSITION, 2, 1, -2);

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
        
        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) RLG_ToggleLight(0);
        if (IsKeyPressed(KEY_R)) RLG_ToggleLight(1);
        if (IsKeyPressed(KEY_G)) RLG_ToggleLight(2);
        if (IsKeyPressed(KEY_B)) RLG_ToggleLight(3);

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                RLG_DrawModel(plane, Vector3Zero(), 1.0f, WHITE);
                RLG_DrawModel(cube, Vector3Zero(), 1.0f, WHITE);

                // Draw spheres to show where the lights are
                for (int i = 0; i < RLG_GetLightcount(); i++)
                {
                    if (RLG_IsLightEnabled(i))
                    {
                        DrawSphereEx(RLG_GetLightVec3(i, RLG_LIGHT_POSITION),
                            0.2f, 8, 8, RLG_GetLightColor(i, RLG_LIGHT_DIFFUSE));
                    }
                    else
                    {
                        DrawSphereWires(RLG_GetLightVec3(i, RLG_LIGHT_POSITION),
                            0.2f, 8, 8, ColorAlpha(RLG_GetLightColor(i, RLG_LIGHT_DIFFUSE), 0.3f));
                    }
                }

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);
            DrawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadModel(cube);
    UnloadModel(plane);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}