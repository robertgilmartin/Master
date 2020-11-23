#pragma once
#include "Module.h"
#include "imGUI/imgui.h"

class ModuleEditor : public Module
{

public:

	ModuleEditor();
	~ModuleEditor();	
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


public:
	void ShowAboutWindow();
	void GoToGitHub();
	void Configuration();

	void Log(const char* fmt);

	void ShowDockingDisabledMessage();


private:
	
	bool opt_fullscreen = true;

	ImGuiTextBuffer buf;
	bool scrollToBottom;
	bool close_console = true;	

	bool show_app_about  = false;
	bool go_to_GitHub = false;
	bool show_app_config = true;
	
	
};
#define va_start __crt_va_start