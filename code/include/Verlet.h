#pragma once
#include "Mesh.h"
#include "Solver.h"

class Verlet : public Solver
{
private:

public:
	Verlet();

	void Update(Mesh&, float);
};