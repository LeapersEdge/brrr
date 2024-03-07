#pragma once

#include "Color.hpp"
#include "Vector3.hpp"
#include "raylib-cpp.hpp"
#include <string>

class Simbody
{
public:
    Simbody(std::string name);
    Simbody(std::string name, raylib::Color color, bool show_set_options = false);
    Simbody(std::string name, unsigned int width, unsigned int height, raylib::Color color = raylib::Color::Blue(), bool show_set_options = true);
public:
    std::string name;

    raylib::Vector3 position;
    raylib::Vector3 velocity;
    raylib::Vector3 acceleration;

    raylib::Vector3 rotation;
    bool show_set_options;
private:
    raylib::Color color;
    unsigned int width;
    unsigned int height;
public:
    void DrawXY(unsigned int *screen_width, unsigned int *screen_height, unsigned int zoom);
    void DrawXZ(unsigned int *screen_width, unsigned int *screen_height, unsigned int zoom);
    void DrawYZ(unsigned int *screen_width, unsigned int *screen_height, unsigned int zoom);
    void Update_Location(unsigned int miliseconds);
    void Update_Rotation(double rotating_x, double rotating_y, double rotating_z, unsigned int miliseconds);

    void Set_Relative_Acceleration(raylib::Vector3 acceleration);
    void Set_Relative_Acceleration(double acceleration_x, double acceleration_y, double acceleration_z);
};

