#ifndef __ModuleCamera__
#define __ModuleCamera__

#include "MahtGeoLib/Geometry/Frustum.h" 

class ModuleCamera : public Module
{
public:
	ModuleCamera();		
	virtual ~ModuleCamera();


	bool Init();
	update_status Update();
	void SetInitUpFrontRight();
	void SetFrustum();		

	float4x4 modelMatrix();
	float4x4 projectionMatrix();
	float4x4 viewMatrix();

	void CameraRotation(float3& axis, float angle);

	void MouseMotionInput(float xoffset, float offset);
	void WheelTransformation(int wheel);

	void MovementSpeed();
	void Orbit();


	bool CleanUp();
	

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
	//FOV

	float yaw{ -90.0f };
	float pitch{ 0.0f };

	float movementSpeed;
	float lastX = 1280, lastY = 960;
	
	bool orbit = false;
	
};

#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)

#endif // __ModuleCamera__

