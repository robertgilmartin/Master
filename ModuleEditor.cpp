#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleRender.h"
#include "ModuleRenderExercice.h"
#include "ModuleWindow.h"

#include "glew-2.1.0/include/GL/glew.h"

#include "imGUI/imgui_impl_sdl.h"
#include "imGUI/imgui_impl_opengl3.h"

#include <shellapi.h>

#include <string>
#include <vector>


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
    static bool show_app_config = false;    

    

    //Console
    {
        
        ImGui::Begin("Console");   
        ImGui::TextUnformatted(buf.begin());

        if (scrollToBottom) 
        {
            ImGui::SetScrollHere(1.0f);
        }        
        scrollToBottom = false;

        ImGui::End();
    }
    
    //MenuBar
    {
        ImGui::BeginMainMenuBar();

        //File
        if (ImGui::BeginMenu("File"))
        {            
            //Close Engine
            if (ImGui::MenuItem("Quit"))
            {
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }

        //Tools
        if (ImGui::BeginMenu("Tools"))
        {
            //Configuration
            ImGui::MenuItem("Configuration", NULL, &show_app_config);           
            ImGui::EndMenu();
        }

        //Help
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
    if (show_app_config) { Configuration(); }
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

void ModuleEditor::Configuration()
{
    //Configuration window
    static bool fullscreen = false;
    static bool fullscreen_desktop = false;
    static bool resizable = false;
    static bool borderless = false;
    static float brightness = 1.0f;
    static int width = 1280;
    static int height = 960;

    //Application window
    static char engine_name[20] = TITLE;
    static char organization[20] = "UPC BarcelonaTECH";  
    static float FPS[100] = {};
    static float millisecond[100] = {};
    static int index = 0;
    static double refresh_time = 0.0;
    

    ImGui::Begin("Configuration");
    ImGui::Text("Options");

    if (ImGui::CollapsingHeader("Application"))
    {
        ImGui::InputText("Engine", engine_name, IM_ARRAYSIZE(engine_name));
        ImGui::InputText("Organization", organization, IM_ARRAYSIZE(organization));          

        if (refresh_time == 0.0) { refresh_time = ImGui::GetTime(); }

        while (refresh_time < ImGui::GetTime())
        {       
            FPS[index] = App->exercice->FPS;

            millisecond[index] = App->exercice->frameTime;

            refresh_time += 1.0f / 60.0f;
            if (index < IM_ARRAYSIZE(FPS))
            {
                ++index;
            }
            else
            {
                index = 0;
            }            
        }

        float FPSaverage = 0.0f;
        float MSaverage = 0.0f;

        for (int n = 0; n < IM_ARRAYSIZE(FPS); ++n)
        {
            FPSaverage += FPS[n];
            MSaverage += millisecond[n];
        }

        FPSaverage /= (float)IM_ARRAYSIZE(FPS);
        MSaverage /= (float)IM_ARRAYSIZE(millisecond);


        char title[25];
        sprintf(title, "Framerate %.1f", FPSaverage);
        ImGui::PlotHistogram("##framerate", FPS, IM_ARRAYSIZE(FPS), 0, title, 0.0f, 100.0f, ImVec2(310, 100.0f));
        sprintf(title, "Milliseconds %.1f", MSaverage);
        ImGui::PlotHistogram("##milliseconds", millisecond, IM_ARRAYSIZE(millisecond), 0, title, 0.0f, 40.0f, ImVec2(310, 100.0f));
    }

    if (ImGui::CollapsingHeader("Window"))
    {        
        if (ImGui::Checkbox("Fullscreen", &fullscreen))
        {
            App->window->WindowConfiguration(SDL_WINDOW_FULLSCREEN, true);
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("Fullscreen Desktop", &fullscreen_desktop))
        {
            App->window->WindowConfiguration(SDL_WINDOW_FULLSCREEN_DESKTOP, NULL);
        }
        if (ImGui::Checkbox("Borderless", &borderless))
        {
            App->window->WindowConfiguration(SDL_WINDOW_BORDERLESS, true);
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("Resizable", &resizable))
        {
            App->window->WindowConfiguration(SDL_WINDOW_RESIZABLE, true);
        }    
        if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f, "%.3f"));
        {
            App->window->Brightness(brightness);
        }
        if (ImGui::SliderInt("Width", &width, 0, 1920, "%.3f"));
        {
            App->window->WidhtHeightResizable(width, height);
        }
        if (ImGui::SliderInt("Height", &height, 0, 1080, " %.3f"));
        {
            App->window->WidhtHeightResizable(width, height);
        }
    }   
    if (ImGui::CollapsingHeader("Hardware"))
    {        
        ImGui::Text("SDL Version: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "   2.0");

        ImGui::Text("OpenGL Version: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "2.1.0");

        ImGui::Text("DevIL version: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), " 1.8.0");

        ImGui::Separator();               

        std::string s = std::to_string(SDL_GetCPUCount());
        char const* CPUCores = s.c_str();  
        
        std::string t = std::to_string(SDL_GetCPUCacheLineSize());
        char const* CPUCache = t.c_str();

        ImGui::Text("CPUs:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), CPUCores);
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "(Cache:");        
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), CPUCache);
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "kB)");
         
        std::string r = std::to_string(SDL_GetSystemRAM()/1000);
        char const* RAM = r.c_str();

        ImGui::Text("System RAM:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), RAM);
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "GB");
                
        std::string cps;
                
        if (SDL_HasAVX()) { cps.append("AVX, "); }
        if (SDL_HasAVX2()) { cps.append("AVX2, "); }
        if (SDL_HasAltiVec()) { cps.append("AltiVec, "); }
        if (SDL_HasMMX()) { cps.append("MMX, "); }
        if (SDL_HasRDTSC()) { cps.append("RDTSC, "); }
        if (SDL_HasSSE()) { cps.append("SSE, "); }
        if (SDL_HasSSE2()) { cps.append("SSE2, "); }
        if (SDL_HasSSE3()) { cps.append("SSE3, "); }
        if (SDL_HasSSE41()) { cps.append("SSE41, "); }
        if (SDL_HasSSE42()) { cps.append("SSE42 "); }

        char const* Caps = cps.c_str();

        ImGui::Text("Caps:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), Caps);

        ImGui::Separator();

        const GLubyte* vendor = glGetString(GL_VENDOR); 
        const GLubyte* renderer = glGetString(GL_RENDERER); 
        const GLubyte* version = glGetString(GL_VERSION);
        
        ImGui::Text("GPU:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), reinterpret_cast<const char*>(vendor));

        ImGui::Text("Brand:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), reinterpret_cast<const char*>(renderer));

        ImGui::Text("Version:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), reinterpret_cast<const char*>(version));

        ImGui::Separator();
        
        
    }

    ImGui::End();
}

void ModuleEditor::Log(const char* fmt)
{
    va_list args;
    va_start(args, fmt);
    buf.appendf(fmt, args);
    va_end(args);
    scrollToBottom = true;
}



