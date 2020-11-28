#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercice.h"
#include "SDL.h"
#include "glew-2.1.0/include/GL/glew.h"
#include "MahtGeoLib/Geometry/Frustum.h"
#include "MahtGeoLib/Math/float3x3.h"
#include "MahtGeoLib/Math/Quat.h"
#include "MahtGeoLib/Time/Clock.h"


ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

void ModuleCamera::SetInitUpFrontRight()
{
	Front.Normalized();	
	Right = Cross(Front, WorldUp).Normalized();	
	Up = Cross(Right, Front).Normalized();
}

void ModuleCamera::SetFrustum()
{
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(90.0f), aspectRatio);
	
	frustum.SetPos(cameraPos);
	frustum.SetFront(Front);
	frustum.SetUp(Up);
}

float4x4 ModuleCamera::modelMatrix()
{
	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4.0f), float3(2.0f, 1.0f, 0.0f));

	return model;
}

float4x4 ModuleCamera::projectionMatrix()
{
	float4x4 projectionGL = frustum.ProjectionMatrix();

	return projectionGL;
}

float4x4 ModuleCamera::viewMatrix()
{
	float4x4 viewMatrix = frustum.ViewMatrix();	

	return viewMatrix;
}

bool ModuleCamera::Init()
{
	SetInitUpFrontRight();
	SetFrustum();		

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*(projectionMatrix().v));

	return true;
}

update_status ModuleCamera::Update()
{
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*(viewMatrix().v));
			
	MovementSpeed();	

	if (App->input->Rpressed)
	{
		if (App->input->CheckKey(SDL_SCANCODE_W))
		{
			cameraPos += Front * movementSpeed;
		}
		if (App->input->CheckKey(SDL_SCANCODE_S))
		{
			cameraPos -= Front * movementSpeed;
		}

		if (App->input->CheckKey(SDL_SCANCODE_A))
		{
			cameraPos -= Right * movementSpeed;
		}

		if (App->input->CheckKey(SDL_SCANCODE_D))
		{
			cameraPos += Right * movementSpeed;
		}
	}	

	if (App->input->CheckKey(SDL_SCANCODE_F))
	{
		cameraPos = float3(0, 2, -10);
	}

	if (App->input->CheckKey(SDL_SCANCODE_LALT) && App->input->Lpressed)
	{
		SetInitUpFrontRight();
		cameraPos = float3(0, 2, -10);		
		orbit = true;
	} 

	if (orbit)
	{
		Orbit();
	}

	SetFrustum();
	orbit = false;

	return UPDATE_CONTINUE;
}

void ModuleCamera::MouseMotionInput(float xoffset, float yoffset)
{		
	xoffset *= movementSpeed;
	yoffset *= movementSpeed;

	float oldpitch = pitch;

	yaw += xoffset; 
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	CameraRotation(Right, pitch - oldpitch);
	CameraRotation(WorldUp, -xoffset);

	SetFrustum();
}


void ModuleCamera::CameraRotation(float3& axis, float angle)
{
	Quat rotationMatrix = Quat(axis, DEGTORAD(angle));

	Front = rotationMatrix * Front;
	Up = rotationMatrix * Up;
	Right = rotationMatrix * Right;
}

bool ModuleCamera::CleanUp()
{
	LOG("Destroying camera");

	return true;
}

void ModuleCamera::MovementSpeed()
{
	movementSpeed = 4 * (1/ App->exercice->FPS);

	if (App->input->CheckKey(SDL_SCANCODE_LSHIFT))
	{
		movementSpeed *= 2;
	}
}

void ModuleCamera::Orbit()
{
	const float radius = 10.0f;
	cameraPos.x = sin(SDL_GetTicks()/500) * radius;
	cameraPos.z = cos(SDL_GetTicks()/500) * radius;

	float4x4 view;
	view = float3x3::LookAt(float3(cameraPos.x, 0, cameraPos.z), float3(0, 0, 0), Up, WorldUp);
}

void ModuleCamera::WheelTransformation(int wheel)
{		
	movementSpeed *= 2;
	cameraPos += wheel * Front * movementSpeed;
}