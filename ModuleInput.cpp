#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercice.h"


#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_sdl.h"
#include "imGUI/imgui_impl_opengl3.h"


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
update_status ModuleInput::PreUpdate()
{
    for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
    {
        if (mouse_buttons[i] == KEY_DOWN)
            mouse_buttons[i] = KEY_REPEAT;

        if (mouse_buttons[i] == KEY_UP)
            mouse_buttons[i] = KEY_IDLE;
    }
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
        
        case SDL_MOUSEBUTTONDOWN:                
            mouse_buttons[sdlEvent.button.button] = KEY_DOWN;
            break;

        case SDL_MOUSEBUTTONUP:            
            mouse_buttons[sdlEvent.button.button - 1] = KEY_UP;
            break;      

        case SDL_MOUSEMOTION:
            mouse_motion.x = sdlEvent.motion.xrel;
            mouse_motion.y = sdlEvent.motion.yrel;
            /*if (SDL_BUTTON_LEFT == KEY_REPEAT)
            {
                App->camera->MouseMotionInput(sdlEvent.motion.xrel, -sdlEvent.motion.yrel);
            }*/
            

        /*case SDL_MOUSEWHEEL:
            if (sdlEvent.wheel.y > 0) {
                App->camera->WheelTransformation(1);
            }
            else if (sdlEvent.wheel.y < 0) {
                App->camera->WheelTransformation(-1);
            }            
            break;*/
            
           
            /*if (CheckKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
                App->camera->MouseMotionInput(sdlEvent.motion.xrel, -sdlEvent.motion.yrel);                
            break;*/
        }

       //EDITOR
       ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        if (sdlEvent.type == SDL_QUIT)
            break;
        if (sdlEvent.type == SDL_WINDOWEVENT && sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE && sdlEvent.window.windowID == SDL_GetWindowID(App->window->window))
            break;        
    }

    
    /*keyboard = SDL_GetKeyboardState(NULL);*/

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
int ModuleInput::GetWheelState()
{
    return wheel;
}
const iPoint& ModuleInput::GetMouseMotion() const
{
    return mouse_motion;
}