#pragma once
#include <glm/glm.hpp> 
#include "Mesh.h"

class Verlet
{
private:

public:
	Verlet();

	glm::vec3 gravity;

	void Update(Mesh&, float);
};