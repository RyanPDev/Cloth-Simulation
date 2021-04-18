#pragma once
#include "ParticleSystem.h"
#include "Solver.h"

class Euler : public Solver
{
private:
	int CheckCollisionBox(glm::vec3, glm::vec3);

public:
	Euler();
	void Update(Mesh& mesh, float dt);
};