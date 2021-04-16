#include "Euler.h"

Euler::Euler() : Solver() {}

void Euler::Update(Mesh& mesh, float dt)
{
	glm::vec3 iPos, iV, auxPos, auxV;
	int counter = 0;
	// per cada part�cula
	for (int i = 0; i < mesh.currentParticles; i++)
	{
		iPos = mesh.positions[i];
		iV = mesh.celerities[i];

		mesh.positions[i] = mesh.positions[i] + mesh.celerities[i] * dt;
		mesh.celerities[i] = mesh.celerities[i] + (gravity * dt);

		// Collision Sphere
		if (CheckCollisionSphere(mesh.positions[i], sphere.c, sphere.r))
		{
			glm::vec3 colPos = GetCollisionPoint(iPos, mesh.positions[i], sphere.c, sphere.r);
			glm::vec3 norm = GetCollisionNorm(colPos, sphere.c);
			ReboundPlane(mesh.positions[i], mesh.celerities[i], norm, GetDFromPlane(colPos, norm));
		}

		// Collision Capsule
		//CollisionCilinder(iPos, mesh.positions[i], mesh.celerities[i]);

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

bool Euler::CheckCollisionSphere(glm::vec3 pos, glm::vec3 sphereCenter, float radius)
{
	return (glm::abs(glm::distance(sphereCenter, pos)) - radius <= 0);
}

void Euler::ReboundPlane(glm::vec3& p, glm::vec3& v, glm::vec3 n, float d)
{
	p = p - ((1 + reboundCoefficient) * (glm::dot(n, p) + d) * n);
	v = v - (1 + reboundCoefficient) * (glm::dot(n, v)) * n;

	glm::vec3 vN = glm::dot(n, v) * n;
	glm::vec3 vT = v - vN;
	v = v - frictionCoefficient * vT;
}