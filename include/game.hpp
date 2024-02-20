#pragma once

#include "debug.hpp"
#include "raylib.h"
#include "raylib-cpp.hpp"
#include "MyGUI.h"
#include "simboat.hpp"
#include <vector>

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
    void Gui_Simboat_Setter_Updates();
private:
    raylib::Camera3D& cam;
    MyGUI gui;

    //raylib::Model model;
    //raylib::Model model2;

    std::vector<Simboat> simboats;
};
