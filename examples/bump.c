#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "../rlights.h"

int main(void)
{
    // Initialization
    InitWindow(800, 600, "bump mapping");

    Camera camera = { 0 };
    camera.position = (Vector3){ 1.2f, 0.4f, 1.2f };
    camera.target = (Vector3){ 0.185f, 0.4f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Generate model
    Image imMap = LoadImage("resources/cubicmap.png");
    Texture2D cubicmap = LoadTextureFromImage(imMap);
    Mesh mesh = GenMeshCubicmap(imMap, (Vector3){ 1.0f, 1.0f, 1.0f });
    Model model = LoadModelFromMesh(mesh);
    GenMeshTangents(&model.meshes[0]);
    UnloadImage(imMap);

    // Init light system
    RLG_Context rlgCtx = RLG_CreateContext(1);
    RLG_SetContext(rlgCtx);

    RLG_UseMap(MATERIAL_MAP_NORMAL, true);

    RLG_UseLight(0, true);
    RLG_SetLightType(0, RLG_SPOTLIGHT);
    RLG_SetLightValue(0, RLG_LIGHT_ENERGY, 2.0f);
    RLG_SetLightValue(0, RLG_LIGHT_INNER_CUTOFF, 17.5f);
    RLG_SetLightValue(0, RLG_LIGHT_OUTER_CUTOFF, 27.5f);

    // Load and set textures for the model
    Texture2D diffuse = LoadTexture("resources/atlas_albedo.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = diffuse;

    Texture2D normal = LoadTexture("resources/atlas_normal.png");
    model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = normal;

    DisableCursor();    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        UpdateCamera(&camera, CAMERA_FREE);
        RLG_SetViewPositionV(camera.position);

        RLG_SetLightVec3(0, RLG_LIGHT_POSITION, camera.position);
        RLG_SetLightTargetV(0, camera.target);

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                RLG_DrawModel(model, Vector3Zero(), 1.0f, WHITE);
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(cubicmap);
    UnloadTexture(diffuse);
    UnloadTexture(normal);
    UnloadModel(model);

    RLG_DestroyContext(rlgCtx);
    CloseWindow();

    return 0;
}
