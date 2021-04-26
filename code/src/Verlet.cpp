#include "Verlet.h"

Verlet::Verlet() : Solver() {}
Verlet::Verlet(glm::vec3 sphereC, float r, float rebound, float friction, bool useSphereCollision) : Solver(sphereC, r, rebound, friction, useSphereCollision) {}

void Verlet::Update(Mesh& mesh, float dt)
{
	for (int i = 0; i < mesh.maxParticles; i++)
	{
		iPos = mesh.positions[i];
		mesh.positions[i] = mesh.positions[i] + (mesh.positions[i] - mesh.positionsBefore[i]) + mesh.forces[i] * glm::pow(dt, 2.f);

		if (glm::distance(iPos, mesh.positions[i]) > (mesh.LStretch * 0.1))
			mesh.positions[i] = iPos + glm::normalize(mesh.positions[i] - iPos) * (mesh.LStretch * 0.1f);

		if (mesh.useCollision)
		{
			//Collision Sphere
			if (CheckCollisionSphere(mesh.positions[i], sphere.c, sphere.r) && useSphereCollision)
			{
				glm::vec3 colPos = GetCollisionPoint(iPos, mesh.positions[i], sphere.c, sphere.r);
				glm::vec3 norm = GetCollisionNorm(colPos, sphere.c);
				float d = GetDFromPlane(colPos, norm);
				ReboundPlane(mesh.positions[i], iPos, mesh.celerities[i], norm, d, dt);
			}

			//Collision Walls
			for (int p = 0; p < 6; p++)
			{
				if ((glm::dot(box.norms[p], iPos) + box.d[p]) * (glm::dot(box.norms[p], mesh.positions[i]) + box.d[p]) <= 0)
					ReboundPlane(mesh.positions[i], iPos, mesh.celerities[i], box.norms[p], box.d[p], dt);
			}
		}
	
		mesh.celerities[i] = (mesh.positions[i] - iPos) / dt;
		mesh.positionsBefore[i] = iPos;
	}
}

void Verlet::ReboundPlane(glm::vec3& p, glm::vec3& p2, glm::vec3& v, glm::vec3 n, float d, float dt)
{
	p -= (1 + reboundCoefficient) * (glm::dot(n, p) + d) * n;
	v -= (1 + reboundCoefficient) * (glm::dot(n, v)) * n;

	if (glm::dot(n, p) + d == 0.f) p += n * 0.001f;

	glm::vec3 vN = glm::dot(n, v) * n;
	glm::vec3 vT = v - vN;

	v = v - frictionCoefficient * vT;
	p2 = -v * dt + p;
}