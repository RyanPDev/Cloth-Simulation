#include "Mesh.h"

Mesh::Mesh() : width(10), height(10), ke(1), kb(1), ks(1) {}

Mesh::Mesh(int _width, int _height) : ke(1), kb(1), ks(1), width(_width), height(_height), initPos(-1.4, 5, 0), ParticleSystem(_width* _height)
{
	//Initialize mesh positions
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			positions[GetIndex(row, col)] = glm::vec3(initPos.x + (col * 0.2), initPos.y - (row * 0.2), initPos.z);
			positionsBefore[GetIndex(row, col)] = glm::vec3(initPos.x + (col * 0.2), initPos.y - (row * 0.2), initPos.z);
			celerities[GetIndex(row, col)] = glm::vec3(0, 0, 0);
		}
	}
}

int Mesh::GetIndex(int _row, int _col) { return _row * width + _col; }

void Mesh::GetSpringForces()
{
	glm::vec3 n = glm::normalize(positions[GetIndex(0, 0)] - positions[GetIndex(0, 1)]);
	//F = -k(|| P1 - P2 || -L12) (P1 - P2 / ||P1 - P2 || ));
	forces[GetIndex(0, 0)] = (glm::vec3)(-(ke * (glm::distance(positions[GetIndex(0, 0)], positions[GetIndex(0, 1)]) - 0.5))) * n;
	forces[GetIndex(0, 1)] = -forces[GetIndex(0, 0)];
}