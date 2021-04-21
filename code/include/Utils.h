#pragma once
#include <glm/glm.hpp> 
#include <glm/vec3.hpp>

static float Pitagoras(float x, float y)
{
	return glm::sqrt(glm::pow(x, 2) + glm::pow(y, 2));
}

static glm::vec3 mirror_point(float a, float b, float c, float d, float x1, float y1, float z1)
{
	float k = (-a * x1 - b * y1 - c * z1 - d) / (float)(a * a + b * b + c * c);

	float x2 = a * k + x1;
	float y2 = b * k + y1;
	float z2 = c * k + z1;

	float x3 = 2 * x2 - x1;
	float y3 = 2 * y2 - y1;
	float z3 = 2 * z2 - z1;

	return glm::vec3(x3, y3, z3);
}
