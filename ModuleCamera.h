#ifndef __ModuleCamera__
#define __ModuleCamera__

#include "MahtGeoLib/Geometry/Frustum.h" 

class ModuleCamera : public Module
{
public:
	ModuleCamera();		
	bool Init();
	update_status Update();
	void SetInitUpFrontRight();
	void SetFrustum();		
	float4x4 modelMatrix();
	float4x4 projectionMatrix();
	float4x4 viewMatrix();
	void MouseMotionInput(float xoffset, float offset);
	void WheelTransformation(int wheel);
	bool CleanUp();
	virtual ~ModuleCamera();


private:

	Frustum frustum;	
	float3 cameraPos = float3(0, 2, -10);
	float3 Front = float3::unitZ;
	float3 WorldUp = float3::unitY;
	float3 Up;	
	float3 Right;	
	float nearPlane{ 0.1f };
	float farPlane{ 200.0f };
	float aspectRatio = SCREEN_WIDTH/SCREEN_HEIGHT;
	float yaw{ -90.0f };
	float pitch{ 0.0f };

	
};

#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)

#endif // __ModuleCamera__

