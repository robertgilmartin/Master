#pragma once
#include "assimp/scene.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);

private:
	unsigned vbo, ebo, vao;
	int material_index, num_vertices, num_indices;
};

