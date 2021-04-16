#include "Solver.h"

Solver::Solver() : gravity(0, -9.81, 0) {}

float Solver::GetDistanceFromPlane(int plane, glm::vec3 pos)
{
	float distance = 0;
	distance = (glm::abs((box.norms[plane].x * pos.x) + (box.norms[plane].y * pos.y) + (box.norms[plane].z * pos.z) + box.d[plane])) /
		(glm::sqrt(glm::pow(box.norms[plane].x, 2) + glm::pow(box.norms[plane].y, 2) + glm::pow(box.norms[plane].z, 2)));

	return distance;
}

glm::vec3 Solver::GetCollisionNorm(glm::vec3 collisionPos, glm::vec3 sphereC)
{
	return glm::normalize(collisionPos - sphereC);
}