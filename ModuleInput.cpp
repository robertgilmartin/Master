#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercice.h"
#include "Model.h"


#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_sdl.h"
#include "imGUI/imgui_impl_opengl3.h"


ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}
update_status ModuleInput::PreUpdate()
{    
    return UPDATE_CONTINUE;
}


// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    mouse_motion = { 0, 0 };

    wheel = 0;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            return UPDATE_STOP; 

        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
            break;
                    
        case SDL_MOUSEBUTTONUP:
            if (sdlEvent.button.button == SDL_BUTTON_LEFT) { Lpressed = false; }
            if (sdlEvent.button.button == SDL_BUTTON_RIGHT) { Rpressed = false; }
            break;

        case SDL_MOUSEBUTTONDOWN: 
            if (sdlEvent.button.button == SDL_BUTTON_LEFT) { Lpressed = true; } 
            if (sdlEvent.button.button == SDL_BUTTON_RIGHT) { Rpressed = true; }
            break;
        
        case SDL_MOUSEMOTION:
            mouse_motion.x = sdlEvent.motion.xrel;
            mouse_motion.y = sdlEvent.motion.yrel;
            break;

        case SDL_MOUSEWHEEL:
            if (sdlEvent.wheel.y > 0) 
            {
                App->camera->WheelTransformation(1);
            }
            else if (sdlEvent.wheel.y < 0) 
            {
                App->camera->WheelTransformation(-1);
            }            
            break;            

        case SDL_DROPFILE:
            /*App->model->DeleteScene();*/
            dropFilePath = sdlEvent.drop.file;
            GetModelPath(dropFilePath);

            //No pilla bé el path
            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_INFORMATION,
                "File dropped on window",
                dropFilePath, App->window->window);

            //Delete previous 
            
            SDL_free(dropFilePath);    
            break;
        }

       //EDITOR
       ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        if (sdlEvent.type == SDL_QUIT)
            break;
        if (sdlEvent.type == SDL_WINDOWEVENT && sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE && sdlEvent.window.windowID == SDL_GetWindowID(App->window->window))
            break;        
    }    
    
    if (Lpressed)
    {
        App->camera->MouseMotionInput(mouse_motion.x, -mouse_motion.y);
    }

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
bool ModuleInput::CheckKey(SDL_Scancode key)
{
    SDL_PumpEvents();

    keyboard = SDL_GetKeyboardState(NULL);

    return keyboard[key];    
}


void ModuleInput::GetModelPath(char* path)
{
    App->model->Load(path);
}

void ModuleInput::DeletePreviousScene()
{
    if (true)
    {

    }
}
