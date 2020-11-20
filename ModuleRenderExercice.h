#pragma once
#include "Module.h"
#include "SDL.h"

class ModuleRenderExercice : public Module
{
public:
	SDL_GLContext glContext;
public:
	ModuleRenderExercice();
	~ModuleRenderExercice();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);
	void RenderTriangle();
	void RotateCameraMouse(float xoffset, float yoffset);

private:
	
	unsigned vbo;
	unsigned int program;
#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
};
