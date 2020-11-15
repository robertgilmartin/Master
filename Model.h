#pragma once
#include "assimp/scene.h"
#include <vector>
#include "Mesh.h"
#include "Module.h"

class Model:public Module
{
public:

	Model();
	~Model();

	void Load(const char* filename);
	void LoadTexture(const aiScene* scene);
	void LoadMeshes(const aiScene* scene);
	void Draw();
	std::vector <unsigned> materials;
	std::vector <Mesh> meshes;

};

