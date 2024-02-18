#pragma once

#include "Vector3.hpp"
#include "raylib-cpp.hpp"

class Simboat
{
public:
    Simboat();
private:
    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;

    raylib::Vector3 rotation;
public:
    void Draw();
    void Update_Location(unsigned int miliseconds);

    void Set_Relative_Acceleration(raylib::Vector3 acceleration);
    void Set_Apsolute_Acceleration(raylib::Vector3 acceleration);
    void Set_Rotation(raylib::Vector3 rotation);
    raylib::Vector3 Get_Rotation();
    raylib::Vector3 Get_Acceleration();
    raylib::Vector3 Get_Velocity();
    raylib::Vector3 Get_Position();
};

