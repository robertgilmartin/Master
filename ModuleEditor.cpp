//#include "Globals.h"
//#include "Application.h"
//#include "ModuleEditor.h"
//#include "ModuleRender.h"
//#include "ModuleWindow.h"
//
//#include "imGUI/imgui.h"
//#include "imGUI/imgui_impl_sdl.h"
//#include "imGUI/imgui_impl_opengl3.h"
//
//
//ModuleEditor::ModuleEditor()
//{}
//
//ModuleEditor::~ModuleEditor()
//{}
//
//
//bool ModuleEditor::Init()
//{
//    ImGui::CreateContext();
//    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->glContext);
//    ImGui_ImplOpenGL3_Init();
//
//    return true;
//}
//
//update_status ModuleEditor::PreUpdate()
//{
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplSDL2_NewFrame(App->window->window);
//    ImGui::NewFrame();
//
//    return UPDATE_CONTINUE;
//}
//
//
//update_status ModuleEditor::Update()
//{
//    ImGui::ShowDemoWindow();
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//    return UPDATE_CONTINUE;
//}
//
//update_status ModuleEditor::PostUpdate()
//{
//    return UPDATE_CONTINUE;
//}
//
//bool ModuleEditor::CleanUp()
//{
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplSDL2_Shutdown();
//    ImGui::DestroyContext();
//
//    return true;
//}