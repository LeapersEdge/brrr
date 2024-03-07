#include "MyGUI.h"
#include "imgui.h"
#include <raylib.h>
#include <string>

MyGUI::MyGUI(bool dark_theme)
    :
    open_main_dockspace(true)
{
    rlImGuiSetup(dark_theme);

    // enabling docking for dockerspaces
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    main_dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
}

void MyGUI::Render()
{
    rlImGuiBegin();

    // render gui ----------------------
    
    // setting up main windoow (dockable and main menu bar)
    Setup_Main_Docking_Window(&open_main_dockspace);
    Show_All_Simbody_Data_Info();

    // ImGui::ShowDemoWindow();
    

    // ---------------------------------

    rlImGuiEnd();
}

void MyGUI::Shutdown()
{
    rlImGuiShutdown();
}

void MyGUI::HelpMarker(const char *desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void MyGUI::Show_Main_Menu_Bar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Toggle Autorun", NULL, this->simboat_autorun))
                this->simboat_autorun ^= 1;

            

            ImGui::EndMenu();
        }

        Show_Main_Menu_Bar_View();

        ImGui::EndMenuBar();
    }
}

void MyGUI::Setup_Main_Docking_Window(bool* open)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    // setting up viewpoint
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    // setting up flags
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;
    
    // removing padding just in case
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    // creating dockspace
    ImGui::Begin("Dockspace", open, window_flags);

    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);
    
    // submit the dockspace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), main_dockspace_flags);
    }
    else
    {
        std::cout << "ERROR: Docking is not enabled! See Demo > Configuration.\n";
        std::cout << "Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code.\n";
    }

    Show_Main_Menu_Bar();

    ImGui::End();
}

void MyGUI::Show_Main_Menu_Bar_View()
{
    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::BeginMenu("Appearence"))
        {
            if (ImGui::BeginMenu("Themes"))
            {
                if (ImGui::MenuItem("Light"))   { ImGui::StyleColorsLight(); }
                if (ImGui::MenuItem("Dark"))    { ImGui::StyleColorsDark(); }
                if (ImGui::MenuItem("Classic")) { ImGui::StyleColorsClassic(); }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Left  split screen projection"))
        {
            if (ImGui::MenuItem("X> Y^", NULL, left_split_screen_projection_index == 0))
                left_split_screen_projection_index = 0;
            if (ImGui::MenuItem("X> Z^", NULL, left_split_screen_projection_index == 1))
                left_split_screen_projection_index = 1;
            if (ImGui::MenuItem("Y> Z^", NULL, left_split_screen_projection_index == 2))
                left_split_screen_projection_index = 2;

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Right split screen projection"))
        {
            if (ImGui::MenuItem("X> Y^", NULL, right_split_screen_projection_index == 0))
                right_split_screen_projection_index = 0;
            if (ImGui::MenuItem("X> Z^", NULL, right_split_screen_projection_index == 1))
                right_split_screen_projection_index = 1;
            if (ImGui::MenuItem("Y> Z^", NULL, right_split_screen_projection_index == 2))
                right_split_screen_projection_index = 2;

            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Toggle show value set options", NULL, show_set_options))
            show_set_options ^= 1;
        
        if (ImGui::BeginMenu("Zoom scale"))
        {
            if (ImGui::MenuItem("x1", NULL, scene_zoom == 1))
                scene_zoom = 1;
            if (ImGui::MenuItem("x2", NULL, scene_zoom == 2))
                scene_zoom = 2;
            if (ImGui::MenuItem("x5", NULL, scene_zoom == 5))
                scene_zoom = 5;           
            if (ImGui::MenuItem("x10", NULL, scene_zoom == 10))
                scene_zoom = 10;           
            if (ImGui::MenuItem("x25", NULL, scene_zoom == 25))
                scene_zoom = 25;           

            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }
}

void MyGUI::Show_All_Simbody_Data_Info()
{
    if (simbody_presenting_data == nullptr)
        return;
    if (simbody_presenting_data->size() != simboat_set_acceleration.size())
    {
        simboat_set_acceleration.resize(simbody_presenting_data->size(), {0,0,0});
        simboat_set_rotation.resize(simbody_presenting_data->size(), {0,0,0});
        simboat_set_velocity.resize(simbody_presenting_data->size(), {0,0,0});
        simboat_set_position.resize(simbody_presenting_data->size(), {0,0,0});
    
        should_set_simboat_relative_acceleration.resize(simbody_presenting_data->size(), false);
        should_set_simboat_acceleration.resize(simbody_presenting_data->size(), false);
        should_set_simboat_position.resize(simbody_presenting_data->size(), false);
        should_set_simboat_velocity.resize(simbody_presenting_data->size(), false);
        should_set_simboat_rotation.resize(simbody_presenting_data->size(), false);
    }

    ImGui::Begin("Simboat Data Controll Panel");

    if (!this->simboat_autorun)
    {
        if (ImGui::Button("Next Tick"))
            this->simboat_time_tick = true;
    }

    ImGui::End();
    
    for (int i = 0; i < simbody_presenting_data->size(); i++)
    {
        Show_Simbody_Data_Info_Window(simbody_presenting_data->at(i), i); 
    }
}

void MyGUI::Show_Simbody_Data_Info_Window(Simbody *body, int i)
{
    ImGui::Begin(body->name.c_str());

    ImGui::Text("Position:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->position.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->position.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->position.z).c_str());

    ImGui::Text("Velocity:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->velocity.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->velocity.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->velocity.z).c_str());

    ImGui::Text("Acceleration:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->acceleration.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->acceleration.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->acceleration.z).c_str());

    ImGui::Text("Rotation:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->rotation.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->rotation.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(body->rotation.z).c_str());

    if (!body->show_set_options)
    {
        ImGui::End();
        return;
    }

    ImGui::Text(" ");

    ImGui::Text("Set Data:");
    ImGui::DragFloat3(("Boat " + std::to_string(i) + " Position").c_str(), &simboat_set_position[i].x);
    ImGui::DragFloat3(("Boat " + std::to_string(i) + " Velocity").c_str(), &simboat_set_velocity[i].x);
    ImGui::DragFloat3(("Boat " + std::to_string(i) + " Acceleration").c_str(), &simboat_set_acceleration[i].x);
    ImGui::DragFloat3(("Boat " + std::to_string(i) + " Rotation").c_str(), &simboat_set_rotation[i].x);

    if (ImGui::Button(("Set Position " + std::to_string(i)).c_str())) 
        should_set_simboat_position[i] = true;  

    ImGui::SameLine();
    if (ImGui::Button(("Set Velocity " + std::to_string(i)).c_str())) 
        should_set_simboat_velocity[i] = true;  

    ImGui::SameLine();
    if (ImGui::Button(("Set Acceleration " + std::to_string(i)).c_str())) 
        should_set_simboat_acceleration[i] = true;

    if (ImGui::Button(("Set Relative Acceleration " + std::to_string(i)).c_str())) 
        should_set_simboat_relative_acceleration[i] = true;

    ImGui::SameLine();
    if (ImGui::Button(("Set Rotation " + std::to_string(i)).c_str())) 
        should_set_simboat_rotation[i] = true;

    ImGui::End();
}
