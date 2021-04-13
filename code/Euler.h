#pragma once
#include "ParticleSystem.h"
#include <glm/glm.hpp> 

class Euler
{
private:
	struct BoxCollider
	{
		glm::vec3 pos[2] = { glm::vec3(-5.f, 0.f, -5.f), glm::vec3{5.f, 10.f, 5.f} };
		glm::vec3 norms[6] = {
			glm::vec3(0.f,  1.f,  0.f),
			glm::vec3(1.f,  0.f,  0.f),
			glm::vec3(0.f,  0.f,  1.f),
			glm::vec3(0.f, -1.f,  0.f),
			glm::vec3(-1.f,  0.f,  0.f),
			glm::vec3(0.f,  0.f, -1.f)
		};
		float d[6] = { 0.f, 5.f, 5.f, 10.f, 5.f, 5.f };
	}box;

	struct SphereCollider
	{
		glm::vec3 c = { 0.f, 4.f, 0.f };
		float r = 1.f;
	};

	struct CapsuleCollider
	{
		glm::vec3 pos[2] = { glm::vec3(-3.f, 2.f, 0.f), glm::vec3(-3.f, 2.f, 2.f) };
		float r = 1.f;
	};

	int CheckCollisionBox(glm::vec3, glm::vec3);
	bool CheckCollisionSphere(glm::vec3, glm::vec3, float);
	void CollisionCilinder(glm::vec3, glm::vec3&, glm::vec3&);
	void ReboundPlane(glm::vec3&, glm::vec3&, glm::vec3, float);
	float GetDistanceFromPlane(int, glm::vec3);
	float GetDFromPlane(glm::vec3, glm::vec3);
	glm::vec3 GetCollisionPoint(glm::vec3, glm::vec3, glm::vec3, float);
	glm::vec3 Euler::GetCollisionNorm(glm::vec3, glm::vec3);

public:
	Euler();
	float reboundCoefficient = 1.f;
	float frictionCoefficient = 1.f;
	glm::vec3 gravity = { 0, -9.8f, 0 };
	void Update(ParticleSystem& ps, float dt);
	SphereCollider sphere;
	CapsuleCollider capsule;
};