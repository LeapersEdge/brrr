#include "MyGUI.h"

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


    //ImGui::ShowDemoWindow();

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
            ImGui::MenuItem("Nothing for now", "", false, false);
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

