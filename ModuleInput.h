#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__

#include "Module.h"

#include "SDL_scancode.h"

#include "Point.h"

typedef unsigned __int8 Uint8;

#define NUM_MOUSE_BUTTONS 5

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();
	bool CheckKey(SDL_Scancode key);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();	
	
	void DeletePreviousScene();
	void GetModelPath(const char* path);

public:
	iPoint mouse_motion;
	int wheel;
	char* dropFilePath;
	bool Lpressed = false;
	bool Rpressed = false;

private:
	const Uint8 *keyboard = NULL;	
	
	
};

#endif // __MODULEINPUT_H__