#pragma once

#include "debug.hpp"
#include "raylib.h"
#include "raylib-cpp.hpp"
#include "MyGUI.h"
#include "simbody.hpp"
#include <vector>
#include <fstream>
#include "simboat.hpp"

class Game
{
public:
    Game(raylib::Camera2D& cam1, raylib::Camera2D& cam2, unsigned int *screen_width, unsigned int *screen_height);

    void Init();
    void Shutdown();

    void Update();
    void Render_Cam1();
    void Render_Cam2();
    void Post_Update();
private:
    void Gui_Simboat_Setter_Updates();
private:
    unsigned int *screen_width;
    unsigned int *screen_height;
    raylib::Camera2D& cam1;
    raylib::Camera2D& cam2;
    MyGUI gui;

    //raylib::Model model;
    //raylib::Model model2;

    Simboat simboat;

    std::vector<Simbody*> simboats;
};
