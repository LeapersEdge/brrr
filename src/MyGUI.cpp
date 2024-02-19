#include "MyGUI.h"
#include "imgui.h"
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
    Show_Simboat_Data_Info();

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
            if (ImGui::MenuItem("Toggle Autorun"))
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
        
        ImGui::EndMenu();
    }
}

void MyGUI::Show_Simboat_Data_Info()
{
    if (simboat_presenting_data == nullptr)
        return;

    ImGui::Begin("Simboat Data");
   
    ImGui::Text("Position:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->position.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->position.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->position.z).c_str());

    ImGui::Text("Velocity:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->velocity.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->velocity.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->velocity.z).c_str());

    ImGui::Text("Acceleration:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->acceleration.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->acceleration.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->acceleration.z).c_str());

    ImGui::Text("Rotation:");
    ImGui::Text("  X: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->rotation.x).c_str());
    ImGui::Text("  Y: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->rotation.y).c_str());
    ImGui::Text("  Z: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(simboat_presenting_data->rotation.z).c_str());

    if (!this->simboat_autorun)
        if (ImGui::Button("Next Tick"))
            this->simboat_time_tick = true;

    if (ImGui::CollapsingHeader("Set Data"))
    {
        ImGui::DragFloat3("Position", simboat_position_set);
        ImGui::DragFloat3("Velocity", simboat_velocity_set);
        ImGui::DragFloat3("Acceleration", simboat_acceleration_set);
        ImGui::DragFloat3("Rotation", simboat_rotation_set);
        
        if (ImGui::Button("Set Position")) 
            should_set_simboat_position = true;  
        
        ImGui::SameLine();
        if (ImGui::Button("Set Velocity")) 
            should_set_simboat_velocity = true;  
        
        ImGui::SameLine();
        if (ImGui::Button("Set Acceleration")) 
            should_set_simboat_acceleration = true;
    
        if (ImGui::Button("Set Relative Acceleration")) 
            should_set_simboat_relative_acceleration = true;
    
        ImGui::SameLine();
        if (ImGui::Button("Set Rotation")) 
            should_set_simboat_rotation = true;
    }
    
    ImGui::End();
}
