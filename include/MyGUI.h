#pragma once

#include "Vector3.hpp"
#include "rlImGui.h"
#include "imgui.h"
#include "raylib.h"
#include <string>
#include <iostream>
#include <raylib-cpp.hpp>
#include "simboat.hpp"
#include <vector>

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
    std::vector<Simboat> *simboat_presenting_data = nullptr;

    bool show_set_options = true;
    std::vector<Vector3> simboat_set_position;
    std::vector<Vector3> simboat_set_velocity;
    std::vector<Vector3> simboat_set_acceleration;
    std::vector<Vector3> simboat_set_rotation;
    std::vector<bool> should_set_simboat_acceleration;
    std::vector<bool> should_set_simboat_velocity;
    std::vector<bool> should_set_simboat_position;
    std::vector<bool> should_set_simboat_rotation;
    std::vector<bool> should_set_simboat_relative_acceleration;

    // 0 - XY, 1 - XZ, 2 - YZ
    int left_split_screen_projection_index = 0;    
    int right_split_screen_projection_index = 2;    
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

