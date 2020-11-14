#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include "ModuleCamera.h"

//#include "imGUI/imgui.h"
//#include "imGUI/imgui_impl_sdl.h"
//#include "imGUI/imgui_impl_opengl3.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

bool ModuleInput::CheckKey(SDL_Scancode key)
{
    SDL_PumpEvents();

    keyboard = SDL_GetKeyboardState(NULL);

    return keyboard[key];
}

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

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;


    int xMousePos = 0;
    int yMousePos = 0;

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
        case SDL_MOUSEWHEEL:
            if (sdlEvent.wheel.y > 0) // scroll up
            {
                App->camera->MoveForward();
            }
            else if (sdlEvent.wheel.y < 0) // scroll down
            {
                App->camera->MoveBackwards();
            }
        case SDL_MOUSEBUTTONDOWN:
            if (SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if (sdlEvent.motion.xrel > xMousePos)
                {
                    App->camera->MoveToTheRight();
                }
                if (sdlEvent.motion.xrel < xMousePos)
                {
                    App->camera->MoveToTheLeft();
                }
                //TRANSLATION
            }
            if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
            {
                //ROTATION
            }

        }
        //EDITOOORR!!!

       /* ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        if (sdlEvent.type == SDL_QUIT)
            break;
        if (sdlEvent.type == SDL_WINDOWEVENT && sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE && sdlEvent.window.windowID == SDL_GetWindowID(App->window->window))
            break;*/
    }

    keyboard = SDL_GetKeyboardState(NULL);

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
