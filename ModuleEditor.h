#pragma once
#include "Module.h"


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


private:
	char* buf = "Hello";
	float f{ 0.0f };
};
#define va_start __crt_va_start