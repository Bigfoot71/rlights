#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "../src/rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 4.0f, 6.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Init light system
    RLG_Init(4);
    RLG_EnableNormalMap();
    RLG_EnableSpecularMap();

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
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("resources/cube/albedo.png");
    cube.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/cube/metalness.png");
    cube.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/cube/normal.png");
    cube.materials[0].shader = *RLG_GetShader();
    GenMeshTangents(cube.meshes);

    Model plane = LoadModelFromMesh(GenMeshPlane(10.0f, 10.0f, 1, 1));
    plane.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("resources/plane/albedo.png");
    plane.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/plane/normal.png");
    plane.materials[0].shader = *RLG_GetShader();
    //GenMeshTangents(&plane.meshes[0]);

    // Main game loop
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

                DrawModel(plane, Vector3Zero(), 1.0f, WHITE);
                DrawModel(cube, Vector3Zero(), 1.0f, WHITE);

                // Draw spheres to show where the lights are
                for (int i = 0; i < 4; i++)
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

    RLG_Close();
    CloseWindow();

    return 0;
}