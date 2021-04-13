#include "Verlet.h"

Verlet::Verlet() {}

void Verlet::Update(Mesh& mesh, float dt)
{
	float d = glm::pow(dt, 2);
	glm::vec3 auxPos;
	mesh.GetSpringForces();
	for (int i = 0; i < 2; i++)
	{
		auxPos = mesh.positions[i];
		mesh.positions[i] = mesh.positions[i] + (mesh.positions[i] - mesh.positionsBefore[i]) + mesh.forces[i] * d;
		mesh.positionsBefore[i] = auxPos;
	}
}