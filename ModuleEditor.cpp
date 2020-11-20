#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleRender.h"
#include "ModuleRenderExercice.h"
#include "ModuleWindow.h"


#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_sdl.h"
#include "imGUI/imgui_impl_opengl3.h"

#include <shellapi.h>

ModuleEditor::ModuleEditor()
{}

ModuleEditor::~ModuleEditor()
{}


bool ModuleEditor::Init()
{
    

    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->exercice->glContext);
    ImGui_ImplOpenGL3_Init();

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    return UPDATE_CONTINUE;
}


update_status ModuleEditor::Update()
{
    static bool show_app_about = false;
    static bool go_to_GitHub = false;

    //Console
    {
        
        ImGui::Begin("Console");   

        
        ImGui::End();
    }
    
    //MenuBar
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File"))
        {            
            if (ImGui::MenuItem("Quit"))
            {
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", NULL, &show_app_about);
            ImGui::MenuItem("GitHub",NULL, &go_to_GitHub);
            ImGui::EndMenu();
        }        
        ImGui::EndMainMenuBar();
    }
    if (show_app_about) { ShowAboutWindow(); }
    if (go_to_GitHub) { GoToGitHub(); }
    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());   

    go_to_GitHub = false;

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void ModuleEditor::ShowAboutWindow()
{    
    ImGui::Begin("About");
     
    ImGui::Text("Engine: Nothing to see here.\n");
    ImGui::Text("This is a non-informatic-engineer-Engine, I tryed it.\n");
    ImGui::Text("This Engine is made by Robert Gil Martin.\n");
    ImGui::Text("Libraries:\nSDL.lib\nglew2.1.0.lib\nassimp-vc141-mt.lib\nDevIL.lib\nILU.lib\nILUT.lib\n");
    ImGui::Text("License: MIT License");

    ImGui::End();
}

void ModuleEditor::GoToGitHub()
{    
    ShellExecute(0, 0, "https://github.com/robertgilmartin/Master", 0, 0, SW_SHOW);    
}


