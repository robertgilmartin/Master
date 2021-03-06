#pragma once
#include "Module.h"
#include "SDL.h"
#include "MahtGeoLib/Math/float3.h"
#include "MahtGeoLib/Math/float4.h"

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
	

	float CalculateFPS();

private:
	unsigned vbo;
	unsigned int program;

public:
	double elapsedSeconds{ 0 };

	float FPS;
	float frameTime;
	float MAX_FPS;
	float deltaTime = 0.0f;

	float3 grid;
	float4 background;

#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
	
};
