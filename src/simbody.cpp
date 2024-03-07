#include "simbody.hpp"
#include "Rectangle.hpp"

#include <math.h>
#include <raylib.h>

Simbody::Simbody(std::string name)
    :
    name(name),
    rotation(0.0f, 0.0f, 0.0f),
    acceleration(0.0f, 0.0f, 0.0f),
    velocity(0.0f, 0.0f, 0.0f),
    position(0.0f, 0.0f, 0.0f),
    color(raylib::Color::Blue()),
    width(25),
    height(25)
{
}

Simbody::Simbody(std::string name, raylib::Color color, bool show_set_options)
    :
    name(name),
    rotation(0.0f, 0.0f, 0.0f),
    acceleration(0.0f, 0.0f, 0.0f),
    velocity(0.0f, 0.0f, 0.0f),
    position(0.0f, 0.0f, 0.0f),
    color(color),
    width(25),
    height(25),
    show_set_options(show_set_options)
{
}

Simbody::Simbody(std::string name, unsigned int width, unsigned int height, raylib::Color color, bool show_set_options)
    :
    name(name),
    rotation(0.0f, 0.0f, 0.0f),
    acceleration(0.0f, 0.0f, 0.0f),
    velocity(0.0f, 0.0f, 0.0f),
    position(0.0f, 0.0f, 0.0f),
    color(color),
    width(width),
    height(height),
    show_set_options(show_set_options)
{
}

void Simbody::DrawXY(unsigned int *screen_width, unsigned int *screen_height, unsigned int zoom)
{
    // bitshift >> 1 == devision / 2
    // need to devide width / 4 because half of the screen is split and middle for each split it in their own halves
    // no need for (*screen_width >> 2) + (*screen_width >> 1) + position.x for other camera because were still drawing in the same position on texture, were just drawing it elsewhere on screen
    
    DrawRectangle((*screen_width >> 2) + position.x * zoom, (*screen_height >> 1) - position.y * zoom, width, height, color);
    /*float center_x = (*screen_width >> 2) + position.x;
    float center_y = (*screen_height >> 1) - position.y;
    raylib::Rectangle rect(center_x - (width >> 1), center_y - (height >> 1), center_x + (width >> 1), center_y + (height >> 1));
    DrawRectanglePro(rect, {center_x, center_y}, rotation.z, color);*/
}

void Simbody::DrawXZ(unsigned int *screen_width, unsigned int *screen_height, unsigned int zoom)
{
    // bitshift >> 1 == devision / 2
    // need to devide width / 4 because half of the screen is split and middle for each split it in their own halves
    // no need for (*screen_width >> 2) + (*screen_width >> 1) + position.x for other camera because were still drawing in the same position on texture, were just drawing it elsewhere on screen
    DrawRectangle((*screen_width >> 2) + position.x * zoom, (*screen_height >> 1) - position.z * zoom, width, height, color);
}

void Simbody::DrawYZ(unsigned int *screen_width, unsigned int *screen_height, unsigned int zoom)
{
    // bitshift >> 1 == devision / 2
    // need to devide width / 4 because half of the screen is split and middle for each split it in their own halves
    // no need for (*screen_width >> 2) + (*screen_width >> 1) + position.x for other camera because were still drawing in the same position on texture, were just drawing it elsewhere on screen
    DrawRectangle((*screen_width >> 2) + position.y * zoom, (*screen_height >> 1) - position.z * zoom, width, height, color);
}

void Simbody::Update_Location(unsigned int miliseconds)
{
    velocity += acceleration * miliseconds / 1000.0f;
    position += velocity * miliseconds / 1000.0f;
}

void Simbody::Update_Rotation(double rotating_x, double rotating_y, double rotating_z, unsigned int miliseconds)
{
    this->rotation.x += rotating_x * miliseconds / 1000.0f;
    this->rotation.y += rotating_y * miliseconds / 1000.0f;
    this->rotation.z += rotating_z * miliseconds / 1000.0f;
}

void Simbody::Set_Relative_Acceleration(raylib::Vector3 acceleration)
{
    double sin_alpha = sin(rotation.x);
    double sin_beta  = sin(rotation.y);
    double sin_gama  = sin(rotation.z);
    double cos_alpha = cos(rotation.x);
    double cos_beta  = cos(rotation.y);
    double cos_gama  = cos(rotation.z);

    double R11 = cos_beta * cos_gama;
    double R12 = sin_alpha * sin_beta * cos_gama - cos_alpha * sin_gama;
    double R13 = cos_alpha * sin_beta * cos_gama + sin_alpha * sin_gama;
    double R21 = cos_beta * sin_gama;
    double R22 = sin_alpha * sin_beta * sin_gama + cos_alpha * cos_gama;
    double R23 = cos_alpha * sin_beta * sin_gama - sin_alpha * cos_gama;
    double R31 = -sin_gama;
    double R32 = sin_alpha * cos_beta;
    double R33 = cos_alpha * cos_beta;

    double product_vec_x = R11 * acceleration.x + R12 * acceleration.y + R13 * acceleration.z;
    double product_vec_y = R21 * acceleration.x + R22 * acceleration.y + R23 * acceleration.z;
    double product_vec_z = R31 * acceleration.x + R32 * acceleration.y + R33 * acceleration.z;

    this->acceleration.x = product_vec_x;
    this->acceleration.y = product_vec_y;
    this->acceleration.z = product_vec_z;
}

void Simbody::Set_Relative_Acceleration(double acceleration_x, double acceleration_y, double acceleration_z)
{
    double sin_alpha = sin(rotation.x);
    double sin_beta  = sin(rotation.y);
    double sin_gama  = sin(rotation.z);
    double cos_alpha = cos(rotation.x);
    double cos_beta  = cos(rotation.y);
    double cos_gama  = cos(rotation.z);

    double R11 = cos_beta * cos_gama;
    double R12 = sin_alpha * sin_beta * cos_gama - cos_alpha * sin_gama;
    double R13 = cos_alpha * sin_beta * cos_gama + sin_alpha * sin_gama;
    double R21 = cos_beta * sin_gama;
    double R22 = sin_alpha * sin_beta * sin_gama + cos_alpha * cos_gama;
    double R23 = cos_alpha * sin_beta * sin_gama - sin_alpha * cos_gama;
    double R31 = -sin_gama;
    double R32 = sin_alpha * cos_beta;
    double R33 = cos_alpha * cos_beta;

    double product_vec_x = R11 * acceleration_x + R12 * acceleration_y + R13 * acceleration_z;
    double product_vec_y = R21 * acceleration_x + R22 * acceleration_y + R23 * acceleration_z;
    double product_vec_z = R31 * acceleration_x + R32 * acceleration_y + R33 * acceleration_z;

    this->acceleration.x = product_vec_x;
    this->acceleration.y = product_vec_y;
    this->acceleration.z = product_vec_z;
}

