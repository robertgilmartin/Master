#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercice.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "Model.h"
#include "./DebugDraw/ModuleDebugDraw.h"


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
	
	

	glContext = SDL_GL_CreateContext(App->window->window);
		
	glEnable(GL_DEPTH_TEST);																	// Enable depth test
	glEnable(GL_CULL_FACE);																		// Enable cull backward faces
	glFrontFace(GL_CCW);																		// Front faces will be counter clockwise
	glEnable(SDL_WINDOW_RESIZABLE);


	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	GLenum err = glewInit();
	// … check for errors
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0	
	/*
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
						0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f };*/

	App->model->Load("BakerHouse.fbx");	
		
	return true;
}

update_status ModuleRenderExercice::PreUpdate()
{
	int width, height;

	SDL_GetWindowSize(App->window->window, &width, &height);

	glViewport(0, 0, width, height);

	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	program = App->program->program;

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRenderExercice::Update()
{	
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);

	App->debugDraw->Draw(App->camera->viewMatrix(), App->camera->projectionMatrix(), w, h);

	App->model->Draw();

	/*RenderTriangle();*/


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
	glDeleteBuffers(1, &vbo);
	return true;
}

void ModuleRenderExercice::WindowResized(unsigned width, unsigned height)
{

}

void ModuleRenderExercice::RenderTriangle()
{		
	glBindBuffer(GL_ARRAY_BUFFER, vbo);	
	glEnableVertexAttribArray(0);	
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(float) * 3 * 3));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, App->texture->LoadTexture("Lenna.png"));
	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);

	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), 
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));
	float4x4 view = App->camera->viewMatrix();
	float4x4 projection = App->camera->projectionMatrix();

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

