#pragma once

#include "debug.hpp"
#include "raylib.h"
#include "raylib-cpp.hpp"
#include "MyGUI.h"

class Game
{
public:
    Game(raylib::Camera3D& cam);

    void Init();
    void Shutdown();

    void Update();
    void Render();
    void Post_Update();
private:
    raylib::Camera3D& cam;
    MyGUI gui;

    raylib::Model model;
    raylib::Model model2;
};
