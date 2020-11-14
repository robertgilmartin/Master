#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "SDL.h"
#include "GL/glew.h"
#include "MahtGeoLib/Geometry/Frustum.h"
#include "MahtGeoLib/Math/float3x3.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

void ModuleCamera::SetFrustum()
{
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(90.0f), 1.3f);
	
	frustum.SetPos(cameraPos);
	frustum.SetFront(cameraFront);
	frustum.SetUp(cameraUp);
}

void ModuleCamera::UpdateFrustum()
{
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(90.0f), 1.3f);

	frustum.SetPos(cameraPos);
	frustum.SetFront(cameraFront);
	frustum.SetUp(cameraUp);
}

float4x4 ModuleCamera::modelMatrix()
{
	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4.0f), float3(2.0f, 1.0f, 0.0f));

	return model;
}

float4x4 ModuleCamera::projectionMatrix()
{
	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed();

	return projectionGL;
}

float4x4 ModuleCamera::viewMatrix()
{
	float4x4 viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();

	return viewMatrix;
}

void ModuleCamera::MoveForward()
{
	cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) + cameraFront * 0.5f;
	frustum.SetPos(cameraPos);
}
void ModuleCamera::MoveBackwards()
{
	cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) - cameraFront * 0.5f;
	frustum.SetPos(cameraPos);
}

void ModuleCamera::MoveToTheLeft()
{
	cameraPos = float3(cameraPos.x + 0.005f, cameraPos.y, cameraPos.z);
	frustum.SetPos(cameraPos);
}
void ModuleCamera::MoveToTheRight()
{
	cameraPos = float3(cameraPos.x - 0.005f, cameraPos.y, cameraPos.z);
	frustum.SetPos(cameraPos);
}
void ModuleCamera::MoveUp()
{
	cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) + cameraUp * 0.005f;
	frustum.SetPos(cameraPos);
}
void ModuleCamera::MoveDown()
{
	cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) - cameraUp * 0.005f;;
	frustum.SetPos(cameraPos);
}

void ModuleCamera::Pitch()
{

}

void ModuleCamera::Yaw()
{
	
}

bool ModuleCamera::Init()
{
	SetFrustum();		

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*(projectionMatrix().v));

	return true;
}

update_status ModuleCamera::Update()
{
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*(viewMatrix().v));

	UpdateFrustum();
	/*if (App->input->CheckKey(SDL_SCANCODE_W))
	{
		cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) + cameraFront * 0.005f;
		frustum.SetPos(cameraPos);
	}

	if (App->input->CheckKey(SDL_SCANCODE_S))
	{
		cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) - cameraFront * 0.005f;
		frustum.SetPos(cameraPos);
	}*/

	/*if (App->input->CheckKey(SDL_SCANCODE_A))
	{
		cameraPos = float3(cameraPos.x + 0.005f, cameraPos.y, cameraPos.z);
		frustum.SetPos(cameraPos);
	}

	if (App->input->CheckKey(SDL_SCANCODE_D))
	{
		cameraPos = float3(cameraPos.x - 0.005f, cameraPos.y, cameraPos.z);
		frustum.SetPos(cameraPos);
	}
	if (App->input->CheckKey(SDL_SCANCODE_Q))
	{
		cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) + cameraUp * 0.005f;
		frustum.SetPos(cameraPos);
	}

	if (App->input->CheckKey(SDL_SCANCODE_E))
	{
		cameraPos = float3(cameraPos.x, cameraPos.y, cameraPos.z) - cameraUp * 0.005f;;
		frustum.SetPos(cameraPos);
	}*/
	if (App->input->CheckKey(SDL_SCANCODE_LEFT))
	{
		float3x3 rotationMatrix = float3x3::RotateY(1 * deltaTime);

		vec oldFront = frustum.Front().Normalized();
		frustum.SetFront(rotationMatrix * oldFront);

		vec oldUp = frustum.Up().Normalized();
		frustum.SetUp(rotationMatrix * oldUp);
	}

	if (App->input->CheckKey(SDL_SCANCODE_RIGHT))
	{
		float3x3 rotationMatrix = float3x3::RotateY(-1 * deltaTime);

		vec oldFront = frustum.Front().Normalized();
		frustum.SetFront(rotationMatrix * oldFront);

		vec oldUp = frustum.Up().Normalized();
		frustum.SetUp(rotationMatrix * oldUp);
	}

	if (App->input->CheckKey(SDL_SCANCODE_DOWN))
	{
		float3x3 rotationMatrix = float3x3::RotateX(1 * deltaTime);

		vec oldFront = frustum.Front().Normalized();
		frustum.SetFront(rotationMatrix * oldFront);

		vec oldUp = frustum.Up().Normalized();
		frustum.SetUp(rotationMatrix * oldUp);
	}

	if (App->input->CheckKey(SDL_SCANCODE_UP))
	{
		float3x3 rotationMatrix = float3x3::RotateX(-1 * deltaTime);

		vec oldFront = frustum.Front().Normalized();
		frustum.SetFront(rotationMatrix * oldFront);

		vec oldUp = frustum.Up().Normalized();
		frustum.SetUp(rotationMatrix * oldUp);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	LOG("Destroying camera");

	return true;
}