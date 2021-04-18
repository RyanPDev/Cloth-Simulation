#include "Verlet.h"

Verlet::Verlet() {}
Verlet::Verlet(glm::vec3 sphereC, float r, float rebound, float friction) : Solver(sphereC, r, rebound, friction) {}

void Verlet::Update(Mesh& mesh, float dt)
{
	glm::vec3 auxPos;

	for (int i = 0; i < mesh.maxParticles; i++)
	{
		auxPos = mesh.positions[i];
		mesh.positions[i] = mesh.positions[i] + (mesh.positions[i] - mesh.positionsBefore[i]) + mesh.forces[i] * glm::pow(dt, 2.f);

		if (glm::distance(auxPos, mesh.positions[i]) > (mesh.LStretch * 0.1))
			mesh.positions[i] = auxPos + glm::normalize(mesh.positions[i] - auxPos) * (mesh.LStretch * 0.1f);

		mesh.celerities[i] = (mesh.positions[i] - auxPos) / dt;

		//Collision Sphere
		if (CheckCollisionSphere(mesh.positions[i], sphere.c, sphere.r))
		{
			glm::vec3 colPos = GetCollisionPoint(auxPos, mesh.positions[i], sphere.c, sphere.r);
			glm::vec3 norm = GetCollisionNorm(colPos, sphere.c);
			ReboundPlane(mesh.positions[i], mesh.celerities[i], norm, GetDFromPlane(colPos, norm));
			auxPos = auxPos - norm * (glm::distance(auxPos, colPos) * 2.f);
		}

		//Collision Walls
		for (int p = 0; p < 6; p++)
		{
			if ((glm::dot(box.norms[p], auxPos) + box.d[p]) * (glm::dot(box.norms[p], mesh.positions[i]) + box.d[p]) <= 0) //&& GetDistanceFromPlane(p, auxPos) != 0
			{
				auxPos = auxPos - box.norms[p] * (GetDistanceFromPlane(p, auxPos) * 2.f);

				ReboundPlane(mesh.positions[i], mesh.celerities[i], box.norms[p], box.d[p]);
			}
		}

		mesh.positionsBefore[i] = auxPos;
	}
}