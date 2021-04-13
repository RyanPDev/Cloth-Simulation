#pragma once
#include "ParticleSystem.h"
#include <glm/glm.hpp>

class Mesh : public ParticleSystem
{
private:
	int GetIndex(int,int);

public:
	Mesh();
	Mesh(int, int);

	int width, height;
	glm::vec3 initPos;

	float ke, kb, ks;

	void GetSpringForces();
};