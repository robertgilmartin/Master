#include "Model.h"
#include "Globals.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "ModuleTexture.h"
#include "Application.h"
#include "GL/glew.h"

#include "MemoryLeaks.h"

Model::Model()
{	
}

update_status Model::Update()
{
	
	return UPDATE_CONTINUE;
}

void Model::Load(const char* filename)
{	
	CleanUp();
	const aiScene* scene = import.ReadFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene)
	{
		LoadTexture(scene);
		LoadMeshes(scene);
	}
	else
	{
		LOG("Error loading %s: %s", filename, aiGetErrorString());
	}	
}

void Model::LoadTexture(const aiScene* scene)
{
	aiString file;	
	
	totalMaterials = scene->mNumMaterials;
	for (unsigned i = 0; i < totalMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->LoadTexture(file.data));
		}
	}
}

void Model::LoadMeshes(const aiScene* scene) 
{
	aiString file;	

	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* currentMesh = scene->mMeshes[i];
		
		mesh.LoadVBO(currentMesh);
		mesh.LoadEBO(currentMesh);
		mesh.CreateVAO();
		meshes.push_back(mesh);		
	}
}

void Model::Draw() 
{
	totalMeshes = meshes.size();
	for (unsigned i = 0; i < totalMeshes; ++i) 
	{
		meshes[i].Draw(materials);
	}
}


bool Model::CleanUp()
{
	materials.clear();
	meshes.clear();

	glDeleteBuffers(1, &(mesh.vbo));
	glDeleteBuffers(1, &(mesh.ebo));
	glDeleteBuffers(1, &(mesh.vao));

	import.FreeScene();
	return true;
}

