#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	SDL_GLContext glContext;
	

public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

private:
	unsigned vbo;
	void* context;
	
};
