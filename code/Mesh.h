#pragma once
#include "ParticleSystem.h"

class Mesh : public ParticleSystem
{
private:
	int GetIndex(int,int);

public:
	Mesh();
	Mesh(int, int);

	int width, height;

};