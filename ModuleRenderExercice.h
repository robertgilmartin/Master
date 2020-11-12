#pragma once
#include "Module.h"
#include "Globals.h"
#include "MahtGeoLib/Geometry/Frustum.h" 

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

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

private:
	Frustum frustum;
	float3 cameraPos = float3(0, 1, -4);
	float3 cameraFront = float3::unitZ;
	float3 cameraUp = float3::unitY;
	float4x4 viewMatrix;

	unsigned vbo;
	void* context;
#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)
};
