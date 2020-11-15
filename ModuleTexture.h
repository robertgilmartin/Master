#pragma once

#include "Module.h"


class ModuleTexture : public Module
{

public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();	
	update_status Update();	
	bool CleanUp();
	unsigned LoadTexture(const char* filename);
	
};