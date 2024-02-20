#include "game.hpp"
#include <raylib.h>
#include <cmath>

Game::Game(raylib::Camera3D& cam1, raylib::Camera3D& cam2)
    :
    cam1(cam1),
    cam2(cam2),
    gui(true)//,
    //model(raylib::Mesh::Cube(1.0f, 1.0f, 1.0f)),
    //model2(raylib::Mesh::Cube(1.0f, 1.0f, 1.0f))
{
    //model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = raylib::Color::Blue();
    //model2.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = raylib::Color::Green();
}

void Game::Init()
{
    gui.simboat_presenting_data = &simboats;
    simboats.push_back({raylib::Color::Blue()});
    simboats.push_back({raylib::Color::Green()});
    simboats[1].position.x = 5;
}

void Game::Update()
{
    if (gui.simboat_autorun)
    {   
        for (int i = 0; i < simboats.size(); i++)
            simboats[i].Update_Location(1);
    }
    else if (gui.simboat_time_tick)
    {
        for (int i = 0; i < simboats.size(); i++)
            simboats[i].Update_Location(1);
        gui.simboat_time_tick = false;
    }
}

void Game::Render_Cam1()
{
    for (int i = 0; i < simboats.size(); i++)
        simboats[i].Draw();
}

void Game::Render_Cam2()
{
    for (int i = 0; i < simboats.size(); i++)
        simboats[i].Draw();
}

void Game::Post_Update() 
{
    gui.Render();    
    Gui_Simboat_Setter_Updates();
}

void Game::Gui_Simboat_Setter_Updates()
{
    for (int i = 0; i < gui.simboat_set_acceleration.size(); i++)
    {
        if (gui.should_set_simboat_position[i])
        {
            bool should_set = gui.should_set_simboat_position[i];
            should_set ^= 1;
            gui.should_set_simboat_position[i] = should_set;
            simboats[i].position = gui.simboat_set_position[i];
        }

        if (gui.should_set_simboat_velocity[i])
        {
            bool should_set = gui.should_set_simboat_velocity[i];
            should_set ^= 1;
            gui.should_set_simboat_velocity[i] = should_set;
            simboats[i].velocity = gui.simboat_set_velocity[i];
        }

        if (gui.should_set_simboat_acceleration[i])
        {
            bool should_set = gui.should_set_simboat_acceleration[i];
            should_set ^= 1;
            gui.should_set_simboat_acceleration[i] = should_set; 
            simboats[i].acceleration = gui.simboat_set_acceleration[i];
        }

        if (gui.should_set_simboat_relative_acceleration[i])
        {
            bool should_set = gui.should_set_simboat_relative_acceleration[i];
            should_set ^= 1;
            gui.should_set_simboat_relative_acceleration[i] = should_set;
            simboats[i].Set_Relative_Acceleration(gui.simboat_set_acceleration[i]);
        }

        if (gui.should_set_simboat_rotation[i])
        {
            bool should_set = gui.should_set_simboat_rotation[i];
            should_set ^= 1;
            gui.should_set_simboat_rotation[i] = should_set;
            simboats[i].rotation = gui.simboat_set_rotation[i];
        }
    }
}

