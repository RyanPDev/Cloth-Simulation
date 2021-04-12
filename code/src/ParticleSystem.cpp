#include "..\ParticleSystem.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace LilSpheres {
	extern int firstParticleIdx, particleCount;
	extern const int maxParticles;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

ParticleSystem::ParticleSystem(int _maxParticles) : maxParticles(_maxParticles),
currentParticles(0)
{
	positions = new glm::vec3[maxParticles];
	celerities = new glm::vec3[maxParticles];
	forces = new glm::vec3[maxParticles];
	age = new float[maxParticles];
}

void ParticleSystem::UpdateParticle(int idx, glm::vec3 newPos)
{
	positions[idx] = newPos;
}

void ParticleSystem::UpdateLilSpheres()
{
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = currentParticles;
	float* first_float = &(positions[0].x);

	LilSpheres::updateParticles(0, maxParticles, first_float);
}

void ParticleSystem::SpawnParticle(glm::vec3 position, glm::vec3 celerity)
{
	//UpdateParticle(currentParticles, position);
	positions[currentParticles] = position;
	celerities[currentParticles] = celerity;
	age[currentParticles] = 0.f;
	currentParticles++;
}

void ParticleSystem::UpdateAge(float _dt)
{
	for (int i = 0; i < currentParticles; i++)
	{
		age[i] += _dt;
	}
}

template <typename T>
void ShiftLeft(int count, T* arr, int positionsToShift)
{
	for (int i = 0; i < count - positionsToShift; i++)
	{
		arr[i] = arr[i + positionsToShift];
	}
}

void ParticleSystem::DestroyOldParticles(float _maxAge)
{
	int positionsToShift = 0;
	float currentAge = age[0];
	while (currentAge > _maxAge && positionsToShift <= currentParticles)
	{
		positionsToShift++;
		currentAge = age[positionsToShift];
	}

	ShiftLeft(currentParticles, positions, positionsToShift);
	ShiftLeft(currentParticles, celerities, positionsToShift);
	ShiftLeft(currentParticles, age, positionsToShift);

	currentParticles -= positionsToShift;
	//for (int i = 0; i < currentParticles; i++)
	//{
	//	if (age[i] > _maxAge)
	//	{

	//		float x = positions[i].x;
	//		float z = positions[i].z;
	//		UpdateParticle(i, glm::vec3(x, 0.1f, z));
	//	}
	//}
}