#pragma once

#include "rlImGui.h"
#include "imgui.h"
#include "raylib.h"
#include <string>
#include <iostream>

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

private:
    // private functions -------------------------------
    void HelpMarker(const char* desc);

    void Setup_Main_Docking_Window(bool* open);
    
    void Show_Main_Menu_Bar();
    void Show_Main_Menu_Bar_View();
public:
    // public functions --------------------------------
    MyGUI(MyGUI &other) = delete;
    void operator=(const MyGUI&) = delete;
};

