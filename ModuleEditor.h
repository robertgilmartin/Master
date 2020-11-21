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


private:
	
	ImGuiTextBuffer buf;
	bool scrollToBottom;	
	
};
#define va_start __crt_va_start