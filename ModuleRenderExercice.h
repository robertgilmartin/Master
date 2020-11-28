#pragma once
#include "Module.h"
#include "SDL.h"
#include "MahtGeoLib/Math/float3.h"
#include "MahtGeoLib/Math/float4.h"

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
	/*float3 gridColor = float3(0.501961f, 0.501961f, 0.501961f);*/

	float3 grid;
	float4 background;

#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
};
