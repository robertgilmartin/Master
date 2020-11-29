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
	bool close_console{ true };

	bool show_app_about{ false };
	bool go_to_GitHub{ false };
	bool show_app_config{ true };
	
	float* front{ new float[3] };
	float* up{ new float[3] };
	float* right{ new float[3] };

	float position[3]{ 0.0f, 0.0f, 0.0f };
	float rotation[3]{ 0.0f, 0.0f, 0.0f };
	float scale[3]{ 0.0f, 0.0f, 0.0f };

public:

	float* gridColor{ new float[3]{1.000000f, 0.647059f, 0.000000f} };
	float* bGround{ new float[4]{0.1f, 0.1f, 0.1f, 0.1f } };
};
#define va_start __crt_va_start