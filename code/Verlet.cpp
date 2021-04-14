#include "Verlet.h"

Verlet::Verlet() : gravity(0, -9.81, 0) {}

void Verlet::Update(Mesh& mesh, float dt) 
{
	glm::vec3 auxPos;

	mesh.GetSpringForces(gravity);

	for (int i = 0; i < mesh.maxParticles; i++)
	{
		auxPos = mesh.positions[i];
		mesh.positions[i] = mesh.positions[i] + (mesh.positions[i] - mesh.positionsBefore[i]) + mesh.forces[i] * glm::pow(dt, 2.f);

		if (glm::distance(auxPos, mesh.positions[i]) > (mesh.LStretch * 0.1))
			mesh.positions[i] = auxPos + glm::normalize(mesh.positions[i] - auxPos) * (mesh.LStretch * 0.1f);

		mesh.celerities[i] = (mesh.positions[i] - auxPos) / dt;
		mesh.positionsBefore[i] = auxPos;
	}
}