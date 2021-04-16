#pragma once
#include "ParticleSystem.h"
#include "Solver.h"

class Euler : public Solver
{
private:
	int CheckCollisionBox(glm::vec3, glm::vec3);
	bool CheckCollisionSphere(glm::vec3, glm::vec3, float);
	//void CollisionCilinder(glm::vec3, glm::vec3&, glm::vec3&);
	void ReboundPlane(glm::vec3&, glm::vec3&, glm::vec3, float);
	//float GetDistanceFromPlane(int, glm::vec3);
	//float GetDFromPlane(glm::vec3, glm::vec3);
	//glm::vec3 GetCollisionPoint(glm::vec3, glm::vec3, glm::vec3, float);

public:
	Euler();
	//void Update(ParticleSystem& ps, float dt);
	void Update(Mesh& mesh, float dt);
};