#include "Euler.h"

Euler::Euler() : Solver() {}

void Euler::Update(Mesh& mesh, float dt)
{
	glm::vec3 iPos, iV, auxPos, auxV;
	int counter = 0;
	// per cada partícula
	for (int i = 0; i < mesh.maxParticles; i++)
	{
		iPos = mesh.positions[i];
		iV = mesh.celerities[i];

		mesh.positions[i] = mesh.positions[i] + mesh.celerities[i] * dt;
		mesh.celerities[i] = mesh.celerities[i] + (gravity * dt);

		// Collision Sphere
		if (UseCollision)
			if (CheckCollisionSphere(mesh.positions[i], sphere.c, sphere.r))
			{
				glm::vec3 colPos = GetCollisionPoint(iPos, mesh.positions[i], sphere.c, sphere.r);
				glm::vec3 norm = GetCollisionNorm(colPos, sphere.c);
				ReboundPlane(mesh.positions[i], mesh.celerities[i], norm, GetDFromPlane(colPos, norm));
			}

		while (CheckCollisionBox(iPos, mesh.positions[i]) < 6)
		{
			int collidedPlane = CheckCollisionBox(iPos, mesh.positions[i]);
			ReboundPlane(mesh.positions[i], mesh.celerities[i], box.norms[collidedPlane], box.d[collidedPlane]);
		}
	}
}

int Euler::CheckCollisionBox(glm::vec3 iPos, glm::vec3 pos)
{
	int collidedPlane = 6;
	for (int i = 0; i < 6; i++)
	{
		if ((glm::dot(box.norms[i], iPos) + box.d[i]) * (glm::dot(box.norms[i], pos) + box.d[i]) <= 0 && GetDistanceFromPlane(i, iPos) != 0)
		{
			collidedPlane = i;
			break;
		}
	}
	return collidedPlane;
}