#ifndef __ModuleCamera__
#define __ModuleCamera__

#include "MahtGeoLib/Geometry/Frustum.h" 



class ModuleCamera : public Module
{
public:
	ModuleCamera();
	void MoveForward();
	void MoveBackwards();
	void MoveToTheLeft();
	void MoveToTheRight();
	void MoveUp();
	void MoveDown();
	void Pitch();
	void Yaw();
	void UpdateFrustum();
	bool Init();
	update_status Update();
	void SetFrustum();		
	float4x4 modelMatrix();
	float4x4 projectionMatrix();
	float4x4 viewMatrix();

	bool CleanUp();
	virtual ~ModuleCamera();

private:

	Frustum frustum;	
	float3 cameraPos = float3(0, 1, -4);
	float3 cameraFront = float3::unitZ;
	float3 cameraUp = float3::unitY;
	float nearPlane = 0.1f;
	float farPlane = 200.0f;
	float deltaTime = 0.005f;
	float aspectRatio;
};

#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)

#endif // __ModuleCamera__

