#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercice.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"

#include "ModuleProgram.h"


ModuleRenderExercice::ModuleRenderExercice()
{
}

// Destructor
ModuleRenderExercice::~ModuleRenderExercice()
{
}

// Called before render is available
bool ModuleRenderExercice::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);										// desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);												// we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);													// we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);												// we want to have a stencil buffer with 8 bits
	

	SDL_GL_CreateContext(App->window->window);
		
	glEnable(GL_DEPTH_TEST);																	// Enable depth test
	glEnable(GL_CULL_FACE);																		// Enable cull backward faces
	glFrontFace(GL_CCW);																		// Front faces will be counter clockwise


	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	GLenum err = glewInit();
	// … check for errors
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(90.0f), 1.3f);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);

	frustum.SetPos(cameraPos);
	frustum.SetFront(cameraFront);
	frustum.SetUp(cameraUp);

	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	//Projection
	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed();

	//View
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();

	//Model
	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*(projectionGL.v));

	return true;
}

update_status ModuleRenderExercice::PreUpdate()
{
	int width, height;

	SDL_GetWindowSize(App->window->window, &width, &height);

	glViewport(0, 0, width, height);

	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRenderExercice::Update()
{	
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(App->program->program);
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*(viewMatrix.v));
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercice::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderExercice::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	/*glDeleteBuffers(1, &vbo);*/
	return true;
}

void ModuleRenderExercice::WindowResized(unsigned width, unsigned height)
{
}

