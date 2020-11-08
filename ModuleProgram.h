#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"

class ModuleProgram : public Module
{

public:
	
	unsigned int program;	
	unsigned int vertexCompiled;
	unsigned int fragmentCompiled;

public:
	ModuleProgram();
	~ModuleProgram();
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
	bool Init();
	bool CleanUp();
	
	
private:

};

