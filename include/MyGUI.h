#pragma once

#include "Vector3.hpp"
#include "rlImGui.h"
#include "imgui.h"
#include "raylib.h"
#include <string>
#include <iostream>
#include <raylib-cpp.hpp>
#include "simboat.hpp"

class MyGUI
{
public:
    MyGUI(bool dark_theme);

    void Render();
    void Shutdown();
private:
    // private data ------------------------------------

    // plz no touch this one variable
    bool open_main_dockspace;
    ImGuiDockNodeFlags main_dockspace_flags;

public:
    // public data -------------------------------------
    bool simboat_autorun = false;
    bool simboat_time_tick = false;
    Simboat *simboat_presenting_data = nullptr;
    
    float simboat_acceleration_set[3] = {0,0,0};
    float simboat_velocity_set[3] = {0,0,0};
    float simboat_position_set[3] = {0,0,0};
    float simboat_rotation_set[3] = {0,0,0};
    bool should_set_simboat_acceleration = false;
    bool should_set_simboat_velocity = false;
    bool should_set_simboat_position = false;
    bool should_set_simboat_rotation = false;
    bool should_set_simboat_relative_acceleration = false;

private:
    // private functions -------------------------------
    void HelpMarker(const char* desc);
    void Setup_Main_Docking_Window(bool* open);
    void Show_Main_Menu_Bar();
    void Show_Main_Menu_Bar_View();

    // currently supports only 1 boat
    void Show_Simboat_Data_Info();
public:
    // public functions --------------------------------
    MyGUI(MyGUI &other) = delete;
    void operator=(const MyGUI&) = delete;
};

