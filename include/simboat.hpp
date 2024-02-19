#pragma once

#include "Vector3.hpp"
#include "raylib-cpp.hpp"

class Simboat
{
public:
    Simboat();
public:
    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;

    raylib::Vector3 rotation;
public:
    void Draw();
    void Update_Location(unsigned int miliseconds);

    void Set_Relative_Acceleration(raylib::Vector3 acceleration);
};

