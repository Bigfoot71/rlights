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
    RLG_Init(4);
    RLG_SetSpecular(0.2f, 0.2f, 0.2f);

    RLG_EnableLight(0);
    RLG_SetLightDiffuseC(0, YELLOW);
    RLG_SetLightType(0, RLG_OMNILIGHT);
    RLG_SetLightPosition(0, -2, 1, -2);

    RLG_EnableLight(1);
    RLG_SetLightDiffuseC(1, RED);
    RLG_SetLightType(1, RLG_OMNILIGHT);
    RLG_SetLightPosition(1, 2, 1, 2);

    RLG_EnableLight(2);
    RLG_SetLightDiffuseC(2, GREEN);
    RLG_SetLightType(2, RLG_OMNILIGHT);
    RLG_SetLightPosition(2, -2, 1, 2);

    RLG_EnableLight(3);
    RLG_SetLightDiffuseC(3, BLUE);
    RLG_SetLightType(3, RLG_OMNILIGHT);
    RLG_SetLightPosition(3, 2, 1, -2);

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
                    if (RLG_IsLightEnabled(i)) DrawSphereEx(RLG_GetLightPosition(i), 0.2f, 8, 8, RLG_GetLightDiffuseC(i));
                    else DrawSphereWires(RLG_GetLightPosition(i), 0.2f, 8, 8, ColorAlpha(RLG_GetLightDiffuseC(i), 0.3f));
                }

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);
            DrawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadModel(cube);
    UnloadModel(plane);

    RLG_Close();
    CloseWindow();

    return 0;
}