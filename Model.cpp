#include "Model.h"
#include "Globals.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "ModuleTexture.h"
#include "Application.h"

Model::Model()
{

}
Model::~Model()
{

}


void Model::Load(const char* filename)
{
	const aiScene* scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);
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
	/*materials.reserve(scene->mNumMaterials);*/
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->LoadTexture(file.data));
		}
	}
}

void Model::LoadMeshes(const aiScene* scene) {
	aiString file;
	//meshes.reserve(scene->mNumMeshes);

	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* currentMesh = scene->mMeshes[i];
		Mesh mesh;
		mesh.LoadVBO(currentMesh);
		mesh.LoadEBO(currentMesh);
		mesh.CreateVAO();
		meshes.push_back(mesh);
	}
}

void Model::Draw() {
	for (unsigned i = 0; i < meshes.size(); ++i) {
		meshes[i].Draw(materials);
	}
}