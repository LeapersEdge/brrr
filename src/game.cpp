#include "game.hpp"
#include <raylib.h>
#include <cmath>

Game::Game(raylib::Camera3D& cam)
    :
    cam(cam),
    gui(true),
    model(raylib::Mesh::Cube(1.0f, 1.0f, 1.0f)),
    model2(raylib::Mesh::Cube(1.0f, 1.0f, 1.0f))
{
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = raylib::Color::Blue();
    model2.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = raylib::Color::Green();
}

void Game::Init()
{
    simboat.Set_Relative_Acceleration({1000.0f, 0.0f, 0.0f});
    gui.simboat_presenting_data = &simboat;
}

void Game::Update()
{
    if (gui.simboat_autorun)
    {   
        simboat.Update_Location(1);
    }
    else if (gui.simboat_time_tick)
    {
        simboat.Update_Location(1);
        gui.simboat_time_tick = false;
    }
}

void Game::Render()
{
    simboat.Draw();
}

void Game::Post_Update() 
{
    gui.Render();

    if (gui.should_set_simboat_position)
    {
        gui.should_set_simboat_position ^= 1;
        simboat.position.x = gui.simboat_position_set[0];
        simboat.position.y = gui.simboat_position_set[1];
        simboat.position.z = gui.simboat_position_set[2];
    }

    if (gui.should_set_simboat_velocity)
    {
        gui.should_set_simboat_velocity ^= 1;
        simboat.velocity.x = gui.simboat_velocity_set[0];
        simboat.velocity.y = gui.simboat_velocity_set[1];
        simboat.velocity.z = gui.simboat_velocity_set[2];
    }

    if (gui.should_set_simboat_acceleration)
    {
        gui.should_set_simboat_acceleration ^= 1;
        simboat.acceleration.x = gui.simboat_acceleration_set[0];
        simboat.acceleration.y = gui.simboat_acceleration_set[1];
        simboat.acceleration.z = gui.simboat_acceleration_set[2];
    }

    if (gui.should_set_simboat_relative_acceleration)
    {
        gui.should_set_simboat_relative_acceleration ^= 1;
        simboat.Set_Relative_Acceleration({gui.simboat_acceleration_set[0], gui.simboat_acceleration_set[1], gui.simboat_acceleration_set[2]});
    }

    if (gui.should_set_simboat_rotation)
    {
        gui.should_set_simboat_rotation ^= 1;
        simboat.rotation.x = gui.simboat_rotation_set[0];
        simboat.rotation.y = gui.simboat_rotation_set[1];
        simboat.rotation.z = gui.simboat_rotation_set[2];
    }
} 

