#include "Mesh.h"

Mesh::Mesh() : width(10), height(10) {}

Mesh::Mesh(int _width, int _height) : width(_width), height(_height), ParticleSystem(_width* _height)
{
	float z = 0;

	//initialize mesh positions
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			positions[GetIndex(row, col)] = glm::vec3(row * 0.2, col * 0.2, z);
			celerities[GetIndex(row, col)] = glm::vec3(0, 0, 0);
		}
	}
}

int Mesh::GetIndex(int _row, int _col){	return _row * width + _col;	}