#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();
	bool CheckKey(SDL_Scancode key);
	bool Init();
	update_status Update();
	bool CleanUp();


private:
	const Uint8 *keyboard = NULL;
};