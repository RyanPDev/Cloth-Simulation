#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include "../ParticleSystem.h"
#include "../Emitter.h"
#include "../Euler.h"
#include "../Mesh.h"
#include "../Verlet.h"
#include <glm/glm.hpp>
#include <ctime>

//Exemple
extern void Exemple_GUI();
extern void Exemple_PhysicsInit();
extern void Exemple_PhysicsUpdate(float dt);
extern void Exemple_PhysicsCleanup();

namespace LilSpheres {
	//extern const int maxParticles;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}
namespace Sphere {
	extern void updateSphere(glm::vec3 pos, float radius);
}
namespace Capsule {
	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius);
}

namespace ClothMesh {
	extern void updateClothMesh(float* array_data);
	extern const int numCols;
	extern const int numRows;
}

extern bool renderParticles;
extern bool renderSphere;
extern bool renderCapsule;
extern bool renderCloth;

bool show_test_window = false;

//ParticleSystem ps;
Emitter emitter;
Euler euler;
Verlet verlet;
Mesh mesh;
float angle = 0.f;
int nextParticleIdx = 0.f;
float timer = 0;
float emissionRate = 500.f; // Particles/second
float maxAge = 1.f; // Seconds

void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate

		/*if (ImGui::CollapsingHeader("Particle System"))
		{
			ImGui::InputFloat("Emission rate", &emissionRate, 1.f);
			ImGui::DragFloat("Max age", &maxAge, 0.05f, 0.5f, 10.f);
		}*/

		/*if (ImGui::CollapsingHeader("Emitter"))
		{
			ImGui::DragFloat("Speed", &emitter.speed, 0.05f, 0.f, 20.f);

			ImGui::RadioButton("Cascade", (int*)&emitter.type, (int)Emitter::Type::CASCADE); ImGui::SameLine();
			ImGui::RadioButton("Fountain", (int*)&emitter.type, (int)Emitter::Type::FOUNTAIN);
			switch (emitter.type)
			{
			case Emitter::Type::FOUNTAIN:

				ImGui::DragFloat3("Position", (float*)&emitter.position, 0.05f, -4.5f, 9.5f);
				ImGui::DragFloat("Angle", (float*)&emitter.angle, 0.05f, 0, 180.f);

				break;
			case Emitter::Type::CASCADE:

				ImGui::DragFloat3("Position Cascade 1", (float*)&emitter.endCascadePos, 0.05f, -4.5f, 9.5f);
				ImGui::DragFloat3("Position Cascade 2", (float*)&emitter.position, 0.05f, -4.5f, 9.5f);
				break;
			}
			ImGui::DragFloat3("Direction", (float*)&emitter.direction, 0.05f, -1.f, 1.f);
		}*/
		if (ImGui::CollapsingHeader("Solver"))
		{
			ImGui::DragFloat3("Gravedad", (float*)&euler.gravity, 0.05f, -9.8f, 9.8f);
			ImGui::DragFloat("Elasticidad", &euler.reboundCoefficient, 0.005f, 0.01f, 1.f);
			ImGui::DragFloat("Friccion", &euler.frictionCoefficient, 0.005f, 0.f, 1.f);
		}
		if (ImGui::CollapsingHeader("Sphere"))
		{
			ImGui::DragFloat3("Shpere Pos", (float*)&euler.sphere.c, 0.05f, -9.8f, 9.8f);
			ImGui::DragFloat("Sphere Radius", &euler.sphere.r, 0.005f, 0.3f, 5.f);
		}
		/*if (ImGui::CollapsingHeader("Capsule"))
		{
			ImGui::DragFloat3("Capsule Pos 1", (float*)&euler.capsule.pos[0], 0.05f, -9.8f, 9.8f);
			ImGui::DragFloat3("Capsule Pos 2", (float*)&euler.capsule.pos[1], 0.05f, -9.8f, 9.8f);
			ImGui::DragFloat("Capsule Radius", &euler.capsule.r, 0.005f, 0.3f, 5.f);
		}*/
	}
	ImGui::End();
}

void PhysicsInit()
{
	srand(static_cast<unsigned>(time(nullptr)));
	renderParticles = true;
	renderCloth = true;
	//renderSphere = true;
	euler = Euler();
	mesh = Mesh(ClothMesh::numCols, ClothMesh::numRows);
	Sphere::updateSphere(euler.sphere.c, euler.sphere.r);
	LilSpheres::particleCount = mesh.width * mesh.height;
	//renderCapsule = true;
	//ps = ParticleSystem(10000);
	//emitter = Emitter(Emitter::Type::FOUNTAIN);
	//Capsule::updateCapsule(euler.capsule.pos[0], euler.capsule.pos[1], euler.capsule.r);
}

void PhysicsUpdate(float dt)
{
	Sphere::updateSphere(euler.sphere.c, euler.sphere.r);
	timer += dt;
	ClothMesh::updateClothMesh(&mesh.positions[0].x);
	LilSpheres::updateParticles(0, mesh.width * mesh.height, &mesh.positions[0].x);
	verlet.Update(mesh, dt);
	//Capsule::updateCapsule(euler.capsule.pos[0], euler.capsule.pos[1], euler.capsule.r);
	//ps.DestroyOldParticles(maxAge);
	/*if (ps.maxParticles > maxAge / dt)
		if (timer >= 1 / emissionRate)
		{
			while (timer > 0)
			{
				timer -= 1 / emissionRate;				
				emitter.spawn(ps);
			}

			timer = 0;
		}*/
	//euler.Update(ps, dt);
	//ps.UpdateLilSpheres();
	//ps.UpdateAge(dt);
}

void PhysicsCleanup() {
}