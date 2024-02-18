#include "Camera3D.hpp"
#include "Vector3.hpp"
#include "raylib.h"
#include "raylib-cpp.hpp"
#include "game.hpp"
#include "global_defines.hpp"

int main() {
    int screenWidth = 1280;
    int screenHeight = 720; 
    //int screenWidth = GetMonitorWidth(0);
    //int screenHeight = GetMonitorHeight(0);


    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    SetTargetFPS(60);

    raylib::Camera3D cam({ 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_ORTHOGRAPHIC);

    Game game(cam);  

    game.Init();

    while (!window.ShouldClose())
    {
        game.Update();

        BeginDrawing();
        window.ClearBackground(RAYWHITE);
        
        BeginMode3D(cam);
        game.Render();
        EndMode3D();
        
        game.Post_Update();
        EndDrawing();
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
