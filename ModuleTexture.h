#pragma once

#include "Module.h"


class ModuleTexture : public Module
{

public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();	
	update_status Update();	
	bool CleanUp();
	unsigned LoadTexture(const char* filename);
	
public:

	int textureWidth;
	int textureHeight;
	int pixelDepht;
	int textureFormat;

	bool activeMipmap = false;
	bool activeWrap = false;
	bool wrapS = false;
	bool wrapT = false;
	bool wrapR = false;
	
};