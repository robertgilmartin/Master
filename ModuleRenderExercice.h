#pragma once
#include "Module.h"

class ModuleRenderExercice : public Module
{

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

private:
	
	unsigned vbo;
	unsigned int program;
#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
};
