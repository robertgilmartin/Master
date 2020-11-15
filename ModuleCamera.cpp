#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "SDL.h"
#include "GL/glew.h"
#include "MahtGeoLib/Geometry/Frustum.h"
#include "MahtGeoLib/Math/float3x3.h"
#include "MahtGeoLib/Math/Quat.h"


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

void ModuleCamera::UpdateFrustum()
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
	/*viewMatrix.Transpose();*/

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
	
	
	float cameraSpeed = 0.05f;//DeltaTime Ongoing

	if (App->input->CheckKey(SDL_SCANCODE_W))
	{
		cameraPos += Front * cameraSpeed;
		/*frustum.SetPos(cameraPos);*/
	}

	if (App->input->CheckKey(SDL_SCANCODE_S))
	{
		cameraPos -= Front * cameraSpeed;
	}

	if (App->input->CheckKey(SDL_SCANCODE_A))
	{
		cameraPos -= Right * cameraSpeed;
	}

	if (App->input->CheckKey(SDL_SCANCODE_D))
	{
		cameraPos += Right * cameraSpeed;
	}
	if (App->input->CheckKey(SDL_SCANCODE_Q))
	{
		cameraPos += Up * cameraSpeed;
	}

	if (App->input->CheckKey(SDL_SCANCODE_E))
	{
		cameraPos -= Up * cameraSpeed;
	}
	if (App->input->CheckKey(SDL_SCANCODE_LEFT))
	{						
		float3x3 rotationMatrix = float3x3::RotateY(1 * cameraSpeed);

		Front = rotationMatrix * Front;
		Right = rotationMatrix * Right;
		Up = rotationMatrix * Up;
		
	}

	if (App->input->CheckKey(SDL_SCANCODE_RIGHT))
	{		
		float3x3 rotationMatrix = float3x3::RotateY(-1 * cameraSpeed);

		Front = rotationMatrix * Front;
		Up = rotationMatrix * Up;
		Right = Cross(Front, Up);
	}

	if (App->input->CheckKey(SDL_SCANCODE_DOWN))
	{
		float3x3 rotationMatrix = float3x3::RotateX(1 * cameraSpeed);

		Front = rotationMatrix * Front;
		Up = rotationMatrix * Up;
		Right = rotationMatrix * Right;		
	}

	if (App->input->CheckKey(SDL_SCANCODE_UP))
	{
		float3x3 rotationMatrix = float3x3::RotateX(-1 * cameraSpeed);

		Front = rotationMatrix * Front;
		Up = rotationMatrix * Up;
		Right = rotationMatrix * Right;
	}

	UpdateFrustum();

	return UPDATE_CONTINUE;
}
//void ModuleCamera::MouseMotionInput(float xoffset, float yoffset)
//{
//	float oldPitch = pitch;
//	float sensitivity = 0.1f;
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//
//	RotateCamera(Right, pitch - oldPitch);
//	RotateCamera(WorldUp, -xoffset);
//}
//
//
//void ModuleCamera::RotateCamera(float3& axis, float angle)
//{
//	Quat rotationMatrix = Quat(axis, DEGTORAD(angle));
//
//	Front = rotationMatrix * Front;
//	Up = rotationMatrix * Up;
//	Right = rotationMatrix * Right;
//}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	LOG("Destroying camera");

	return true;
}