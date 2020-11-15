#include "Mesh.h"
#include "glew-2.1.0/include/GL/glew.h"
#include "SDL/include/SDL.h"
#include "MahtGeoLib/Math/float2.h"
#include "MahtGeoLib/Math/float4x4.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "Application.h"

Mesh::Mesh()
{
	vbo = ebo = vao = 0;
	material_index = num_vertices = num_indices = 0;
}

// Destructor
Mesh::~Mesh()
{
}

void Mesh::LoadVBO(const aiMesh* mesh)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	unsigned vertex_size = (sizeof(float) * 5); // 3 vertex coords, 2 texture coords
	unsigned buffer_size = vertex_size * mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);

	/*unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);
	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
	}*/
	float* vertices = (float*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));//GL_Write_Only

	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		*(vertices++) = mesh->mVertices[i].x;
		*(vertices++) = mesh->mVertices[i].y;
		*(vertices++) = mesh->mVertices[i].z;
		*(vertices++) = mesh->mTextureCoords[0][i].x;
		*(vertices++) = mesh->mTextureCoords[0][i].y;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	num_vertices = mesh->mNumVertices;
	material_index = mesh->mMaterialIndex;
}

void Mesh::LoadEBO(const aiMesh* mesh)
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

	for (unsigned i = 0; i < mesh->mNumFaces; ++i)
	{
		assert(mesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	num_indices = mesh->mNumFaces * 3;
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 5), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (sizeof(float) * 5), (void*)(sizeof(float) * 3));

	glBindVertexArray(0);
}

void Mesh::Draw(const std::vector<unsigned>& model_textures)
{
	unsigned program = App->program->program;

	const float4x4& view = App->camera->viewMatrix();
	const float4x4& proj = App->camera->projectionMatrix();
	float4x4 model = float4x4::identity;

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, model_textures[material_index]);
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}