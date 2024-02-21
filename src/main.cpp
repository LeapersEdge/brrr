#include "Camera3D.hpp"
#include "raylib.h"
#include "raylib-cpp.hpp"
#include "game.hpp"
#include "global_defines.hpp"

int main() {
    int screenWidth = 1280;
    int screenHeight = 720; 
    //int screenWidth = GetMonitorWidth(0);
    //int screenHeight = GetMonitorHeight(0);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    raylib::Window window(screenWidth, screenHeight, "brrrr");

    SetTargetFPS(60);

    raylib::Camera2D cam1({0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f, 1.0f);
    raylib::Camera2D cam2({0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f, 1.0f); 
    RenderTexture screen1 = LoadRenderTexture(GetScreenWidth() >> 1, GetScreenHeight());
    RenderTexture screen2 = LoadRenderTexture(GetScreenWidth() >> 1, GetScreenHeight());
    raylib::Rectangle split_screen_rect = {0.0f, 0.0f, (float)screen1.texture.width, (float)-screen1.texture.height};

    unsigned int last_screen_width = GetScreenWidth();
    unsigned int last_screen_height = GetScreenHeight();

    Game game(cam1, cam2, &last_screen_width, &last_screen_height);  

    game.Init();

    while (!window.ShouldClose())
    {
        //raylib::RenderTexture screen1 = LoadRenderTexture(GetScreenWidth() / 2, GetScreenHeight());
        //raylib::RenderTexture screen2 = LoadRenderTexture(GetScreenWidth() / 2, GetScreenHeight());
        //split_screen_rect.width = (float)screen1.texture.width;
        //split_screen_rect.height = (float)-screen1.texture.height;
        if (last_screen_height != GetScreenHeight() || last_screen_width != GetScreenWidth())
        {
            last_screen_width = GetScreenWidth();
            last_screen_height = GetScreenHeight();
            
            UnloadRenderTexture(screen1);
            UnloadRenderTexture(screen2);

            screen1 = LoadRenderTexture(last_screen_width >> 1, last_screen_height);
            screen2 = LoadRenderTexture(last_screen_width >> 1, last_screen_height);
            split_screen_rect.width = (float)screen1.texture.width;
            split_screen_rect.height = (float)-screen1.texture.height;
        }

        game.Update();
        
        BeginTextureMode(screen1);
        ClearBackground(WHITE);
        BeginMode2D(cam1);
        game.Render_Cam1();
        EndMode2D();
        EndTextureMode();

        BeginTextureMode(screen2);
        ClearBackground(WHITE);
        BeginMode2D(cam2);
        game.Render_Cam2();
        EndMode2D();
        EndTextureMode();
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(screen1.texture, split_screen_rect, (Vector2){0, 0}, WHITE);
        DrawTextureRec(screen2.texture, split_screen_rect, (Vector2){(float)(last_screen_width >> 1), 0}, WHITE);
        DrawRectangle((last_screen_width >> 1) - 2, 0, 4, last_screen_height, LIGHTGRAY);
        game.Post_Update();
        EndDrawing();
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
