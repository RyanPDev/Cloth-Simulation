#pragma once
#include "ParticleSystem.h"
#include <glm/glm.hpp>

class Spring;

class Mesh : public ParticleSystem
{
private:

	int GetIndex(int, int);
	bool isInMesh(int, int);
	glm::vec3 CalculateForce(int, int, int, int, float, float, float);

public:
	Mesh();
	Mesh(int, int);

	int width, height;
	float Lstretch, LShear, LBending;
	glm::vec3 initPos;

	float kEStretch, kEShear, kEBend, stretchDamping, shearDamping, bendDamping, kConstraint;

	void GetSpringForces(glm::vec3);
};

//class Spring {
//	Mesh m;
//	int p1Idx, p2Idx;
//	float ke, kd, l;
//	Spring(Mesh _m, int p1_idx, int p2_idx, float _ke, float _kd, float restDistance)
//		: m(_m), p1Idx(p1_idx), p2Idx(p2_idx), ke(_ke), kd(_kd), l(restDistance)
//	{
//
//	}
//	glm::vec3 getP1Force() {
//		glm::vec3 p1 = m.positions[p1Idx];
//		glm::vec3 p2 = m.positions[p2Idx];
//		glm::vec3 v1 = m.celerities[p1Idx];
//		glm::vec3 v2 = m.celerities[p2Idx];
//
//		glm::vec3 force = glm::vec3(0, 0, 0);
//
//		force = static_cast<glm::vec3>((-(ke * (glm::distance(p1, p2) - (l)) + glm::dot(kd * (v1 - v2), glm::normalize(p1 - p2))))) * glm::normalize(p1 - p2);
//		return force;
//	}
//	glm::vec3 getP2Force() {
//		return -getP1Force();
//	}
//};