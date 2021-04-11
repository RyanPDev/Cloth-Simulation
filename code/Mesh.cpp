#include "Mesh.h"

Mesh::Mesh() : width(10), height(10) {}

Mesh::Mesh(int _width, int _height) : width(_width), height(_height), initPos(-1.4, 5, 0), ParticleSystem(_width* _height)
{
	float z = 0;

	//Initialize mesh positions
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			positions[GetIndex(row, col)] = glm::vec3(initPos.x + (col * 0.2), initPos.y - (row * 0.2), initPos.z);
			celerities[GetIndex(row, col)] = glm::vec3(0, 0, 0);
		}
	}
}

int Mesh::GetIndex(int _row, int _col) { return _row * width + _col; }

glm::vec3* Mesh::GetSpringForces()
{
	return nullptr;
}