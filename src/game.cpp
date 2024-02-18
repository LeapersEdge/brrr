#include "game.hpp"
#include <raylib.h>

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

}

void Game::Update()
{

}

void Game::Render()
{
    model.Draw({0.0f, 0.0f, 0.0f});
    model2.Draw({0.0f, 1.0f, 0.0f});
    model2.Draw({1.0f, 0.0f, 0.0f});
    // model2.Draw({0.0f, 0.0f, 1.0f}); // draws over model
}

void Game::Post_Update() 
{
    gui.Render();
} 


