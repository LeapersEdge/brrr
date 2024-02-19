#include "simboat.hpp"

#include <math.h>
#include <raylib.h>

Simboat::Simboat()
    :
    rotation(0.0f, 0.0f, 0.0f),    
    acceleration(0.0f, 0.0f, 0.0f),    
    velocity(0.0f, 0.0f, 0.0f),    
    position(0.0f, 0.0f, 0.0f) 
{
}

void Simboat::Draw()
{
    DrawCube(position, 1.0f, 1.0f, 1.0f, raylib::Color::Blue());
}

void Simboat::Update_Location(unsigned int miliseconds)
{
    velocity += acceleration * miliseconds / 1000.0f;
    position += velocity * miliseconds / 1000.0f;
}

void Simboat::Set_Relative_Acceleration(raylib::Vector3 acceleration)
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


