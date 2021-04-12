#include "Verlet.h"

Verlet::Verlet() {}

void Verlet::Update(Mesh& mesh, float dt)
{
		mesh.GetSpringForces();
	for (int i = 0; i < mesh.maxParticles; i++)
	{
		mesh.forces[i];
		mesh.positions[i] = 0;
		mesh.celerities[i] = 0;
	}
}