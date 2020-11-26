#pragma once
#include "Assimp/include/assimp/scene.h"
#include "assimp/Importer.hpp"
#include <vector>
#include "Mesh.h"
#include "Module.h"

class Model:public Module
{
public:

	Model();
	virtual ~Model() {};

	void Load(const char* filename);
	void LoadTexture(const aiScene* scene);
	void LoadMeshes(const aiScene* scene);
	void Draw();
	std::vector <unsigned> materials;
	std::vector <Mesh> meshes;
	void DeleteScene();
	
	Assimp::Importer import;

};

