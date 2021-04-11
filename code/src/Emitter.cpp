#include "..\Emitter.h"

//std::random_device rd; // obtain a random number from hardware
//std::mt19937 gen(rd()); // seed the generator
//std::uniform_int_distribution<> distr(-1, 1); // define the range
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
Emitter::Emitter() {}
Emitter::Emitter(Type _type) :type(_type)
{
	type = Type::CASCADE;
	position = glm::vec3(0, 1, 0);
	endCascadePos = glm::vec3(2, 1, 2);
	direction = glm::vec3(0, 1, 0);
	speed = 5;
	angle = 30;
}
void Emitter::spawn(ParticleSystem& _ps)
{
	if (_ps.currentParticles < _ps.maxParticles)
	{
		_ps.SpawnParticle(CalcPos(), CalcDir(angle));
	}
}
glm::vec3 Emitter::CalcPos() {
	switch (type)
	{
	case Type::FOUNTAIN:
		break;
	case Type::CASCADE:
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return position + (glm::vec3(endCascadePos - position) * r);
		break;
	}
	return position;
}
glm::vec3 Emitter::CalcDir(int _angle) {
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	glm::vec3 particleDir;
	//return glm::normalize(glm::cos());
	//glm::dot()
	switch (type)
	{
	case Type::FOUNTAIN:
		particleDir = ChangeDir();
		break;
	case Type::CASCADE:
		particleDir = direction;
		break;
	}
	return glm::normalize(particleDir) * speed;
}

glm::vec3 Emitter::ChangeDir()
{
	glm::vec3 randomDir;
	int counter = 0;
	bool isValid = false;
	while(!isValid && counter < 15)
    {
        counter++;

        randomDir = glm::vec3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),static_cast <float> (rand()) / static_cast <float> (RAND_MAX),static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
        randomDir = glm::normalize(randomDir);
        isValid = glm::cos(angle) >= glm::dot(randomDir, direction) / (glm::sqrt(glm::pow(randomDir.x, 2) + glm::pow(randomDir.y, 2) + glm::pow(randomDir.z, 2)) * glm::sqrt(glm::pow(direction.x, 2) + glm::pow(direction.y, 2) + glm::pow(direction.z, 2)));
    }
	if(counter >= 15)
	{
		return direction;
	}
	return randomDir;
}
