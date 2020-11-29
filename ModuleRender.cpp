#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "Model.h"
#include "ModuleEditor.h"
#include "./DebugDraw/ModuleDebugDraw.h"
#include "./DebugDraw/debugdraw.h"
#include "Assimp/cimport.h"
#include <iostream>
#include "MemoryLeaks.h"


ModuleRender::ModuleRender() :
	MAX_FPS{ 60.0f }
{

}

ModuleRender::~ModuleRender()
{
}

void myCallback(const char* msg, char* userData)
{
	App->editor->Log(msg);
}

// Called before render is available
bool ModuleRender::Init()
{

	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);										// desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);												// we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);													// we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);												// we want to have a stencil buffer with 8 bits



	glContext = SDL_GL_CreateContext(App->window->window);

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

	//Console
	struct aiLogStream stream;
	stream.callback = myCallback;
	aiAttachLogStream(&stream);

	//Initial Scene
	
	App->model->Load("BakerHouse.fbx");

	return true;
}

update_status ModuleRender::PreUpdate()
{
	int width, height;

	SDL_GetWindowSize(App->window->window, &width, &height);

	glViewport(0, 0, width, height);

	background.x = App->editor->bGround[0];
	background.y = App->editor->bGround[1];
	background.z = App->editor->bGround[2];
	background.w = App->editor->bGround[3];

	glClearColor(background[0], background[1], background[2], background[3]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program = App->program->program;

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	float starTicks = SDL_GetTicks();
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);

	grid.x = App->editor->gridColor[0];
	grid.y = App->editor->gridColor[1];
	grid.z = App->editor->gridColor[2];

	App->debugDraw->Draw(App->camera->viewMatrix(), App->camera->projectionMatrix(), w, h, grid);

	App->model->Draw();

	//FPS
	CalculateFPS();

	float frameTicks = SDL_GetTicks() - starTicks;
	//Limit FPS
	if (1000.0f / MAX_FPS > frameTicks)
	{
		SDL_Delay(1000.0f / MAX_FPS - frameTicks);
	}
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	
	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{

}

float ModuleRender::CalculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		FPS = 1000.0f / frameTimeAverage;
	}
	else
	{
		FPS = 60.0f;
	}

	return FPS;
}

