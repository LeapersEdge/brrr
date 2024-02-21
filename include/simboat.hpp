#pragma once

#include "Color.hpp"
#include "Vector3.hpp"
#include "raylib-cpp.hpp"

class Simboat
{
public:
    Simboat();
    Simboat(raylib::Color color);
    Simboat(unsigned int width, unsigned int height, raylib::Color color = raylib::Color::Blue());
public:
    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;

    raylib::Vector3 rotation;
private:
    raylib::Color color;
    unsigned int width;
    unsigned int height;
public:
    void DrawXY(unsigned int *screen_width, unsigned int *screen_height);
    void DrawXZ(unsigned int *screen_width, unsigned int *screen_height);
    void DrawYZ(unsigned int *screen_width, unsigned int *screen_height);
    void Update_Location(unsigned int miliseconds);

    void Set_Relative_Acceleration(raylib::Vector3 acceleration);
};

