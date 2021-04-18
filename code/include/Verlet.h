#pragma once
#include "Mesh.h"
#include "Solver.h"

class Verlet : public Solver
{
private:

public:
	Verlet();
	Verlet(glm::vec3, float, float, float);

	void Update(Mesh&, float);
};