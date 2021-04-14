#include "Mesh.h"

float Pitagoras(float x, float y)
{
	return glm::sqrt(glm::pow(x, 2) + glm::pow(y, 2));
}

Mesh::Mesh() : width(10), height(10), kEStretch(1), kEShear(1), kEBend(1), stretchDamping(1), shearDamping(1), bendDamping(1), Lstretch(0.2) {
	LShear = Pitagoras(Lstretch, Lstretch);
	LBending = Lstretch * 2;
}

Mesh::Mesh(int _width, int _height) : kEStretch(1000), kEShear(1000), kEBend(1000), stretchDamping(50), shearDamping(50),
bendDamping(50), width(_width), height(_height), initPos(-3.5, 9, 0), Lstretch(0.2), ParticleSystem(_width* _height)
{
	LShear = Pitagoras(Lstretch, Lstretch);
	LBending = Lstretch * 2;

	//Initialize mesh
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			positions[GetIndex(row, col)] = glm::vec3(initPos.x + (col * Lstretch), initPos.y, initPos.z - (row * Lstretch));
			positionsBefore[GetIndex(row, col)] = positions[GetIndex(row, col)];
			celerities[GetIndex(row, col)] = glm::vec3(0, 0, 0);
		}
	}
}


int Mesh::GetIndex(int _row, int _col) { return _row * width + _col; }

void Mesh::GetSpringForces(glm::vec3 externalForces)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int particleIdx = GetIndex(row, col);
			if (particleIdx == 0 || particleIdx ==  width - 1)
				forces[particleIdx] = glm::vec3(0, 0, 0);
			else
			{
				// Stretch
				forces[particleIdx] = CalculateForce(col + 1, row, col, row, kEStretch, stretchDamping, Lstretch);
				forces[particleIdx] += CalculateForce(col - 1, row, col, row, kEStretch, stretchDamping, Lstretch);
				forces[particleIdx] += CalculateForce(col, row + 1, col, row, kEStretch, stretchDamping, Lstretch);
				forces[particleIdx] += CalculateForce(col, row - 1, col, row, kEStretch, stretchDamping, Lstretch);

				// Shear
				forces[particleIdx] += CalculateForce(col + 1, row + 1, col, row, kEShear, shearDamping, LShear);
				forces[particleIdx] += CalculateForce(col - 1, row - 1, col, row, kEShear, shearDamping, LShear);
				forces[particleIdx] += CalculateForce(col + 1, row - 1, col, row, kEShear, shearDamping, LShear);
				forces[particleIdx] += CalculateForce(col - 1, row + 1, col, row, kEShear, shearDamping, LShear);

				// Bend		
				forces[particleIdx] += CalculateForce(col + 2, row, col, row, kEBend, bendDamping, LBending);
				forces[particleIdx] += CalculateForce(col - 2, row, col, row, kEBend, bendDamping, LBending);
				forces[particleIdx] += CalculateForce(col, row + 2, col, row, kEBend, bendDamping, LBending);
				forces[particleIdx] += CalculateForce(col, row - 2, col, row, kEBend, bendDamping, LBending);

				forces[particleIdx] += externalForces;
			}
		}
	}
}

glm::vec3 Mesh::CalculateForce(int xPos, int yPos, int initX, int initY, float kElasticity, float kDamping, float restLength)
{
	glm::vec3 force = glm::vec3(0, 0, 0);

	if (isInMesh(xPos, yPos))
	{
		force = static_cast<glm::vec3>((-(kElasticity * (glm::distance(positions[GetIndex(initY, initX)], positions[GetIndex(yPos, xPos)]) - (restLength))
			+ glm::dot(kDamping * (celerities[GetIndex(initY, initX)] - celerities[GetIndex(yPos, xPos)]), glm::normalize(positions[GetIndex(initY, initX)] - positions[GetIndex(yPos, xPos)])))))
			* glm::normalize(positions[GetIndex(initY, initX)] - positions[GetIndex(yPos, xPos)]);
	}

	return force;
}

bool Mesh::isInMesh(int xIdx, int yIdx)
{
	return xIdx >= 0 && yIdx >= 0 && yIdx < height && xIdx < width;
}