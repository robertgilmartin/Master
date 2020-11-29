#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_video.h"

class Application;

class ModuleWindow : public Module
{
private:
	bool ret;
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	void CreateAWindow();

	bool Init();

	// Called before quitting
	bool CleanUp();

	void WindowConfiguration(SDL_WindowFlags flag, bool state);

	void Brightness(float brightness);

	void WidhtHeightResizable(int width, int height);

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;

	Uint32 flags;
};

#endif // __ModuleWindow_H__