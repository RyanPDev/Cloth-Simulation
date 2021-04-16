#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include "ParticleSystem.h"
#include "Euler.h"
#include "Mesh.h"
#include "Verlet.h"
#include <ctime>
#include <string>
#include <sstream>

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

Solver solver;
Euler euler;
Verlet verlet;
Mesh mesh;
std::string t;
float timer = 0;
float resetTimer = 5;
bool autoReset = false;
bool usingVerlet = true;
bool playSimulation = false;
bool enableParticles = false;

void ResetSimulation()
{
	timer = 0;
	mesh = Mesh(ClothMesh::numCols, ClothMesh::numRows, glm::vec3(-2.8, 9.5, 4), mesh.LStretch);
	solver = Solver(solver.sphere.c, solver.sphere.r, solver.useCollision);
	euler = Euler();
	verlet = Verlet();
}

void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate

		ImGui::Checkbox("Play simulation", &playSimulation);
		ImGui::Checkbox("Enable particles", &renderParticles);


		ImGui::RadioButton("Euler", (int*)&usingVerlet, 0); ImGui::SameLine();
		ImGui::RadioButton("Verlet", (int*)&usingVerlet, 1);


		ImGui::DragFloat("Stretch rest length", (float*)&mesh.LStretch, 0.005f, 0.1, 1.f);

		if (ImGui::CollapsingHeader("Solver parameters"))
		{
			ImGui::DragFloat3("Gravity", (float*)&solver.gravity, 0.05f, -9.81f, 9.81f);
		}

		if (ImGui::CollapsingHeader("Collision"))
		{
			ImGui::Checkbox("Use Collision", &solver.useCollision);
			if (solver.useCollision)
			{
				ImGui::DragFloat("Elasticidad", &solver.reboundCoefficient, 0.005f, 0.01f, 1.f);
				ImGui::DragFloat("Friccion", &solver.frictionCoefficient, 0.005f, 0.f, 1.f);

				ImGui::Checkbox("Use sphere collider", &renderSphere);

				if (renderSphere)
				{
					ImGui::DragFloat3("Shpere Pos", (float*)&solver.sphere.c, 0.05f, -9.8f, 9.8f);
					ImGui::DragFloat("Sphere Radius", &solver.sphere.r, 0.005f, 0.3f, 5.f);
				}
			}
		}

		if (ImGui::CollapsingHeader("Spring parameters"))
		{
			if (ImGui::CollapsingHeader("Spring's constants"))
			{
				ImGui::DragFloat("K stretch", (float*)&mesh.kEStretch, 5.f, 1, 2000.f);
				ImGui::DragFloat("K shear", (float*)&mesh.kEShear, 5.f, 1, 2000.f);
				ImGui::DragFloat("K bending", (float*)&mesh.kEBend, 5.f, 1, 2000.f);
			}

			if (ImGui::CollapsingHeader("Spring's dampings"))
			{
				ImGui::DragFloat("Stretch damping", (float*)&mesh.stretchDamping, 0.5f, 0.f, 100.f);
				ImGui::DragFloat("Shear damping", (float*)&mesh.shearDamping, 0.5f, 0.f, 100.f);
				ImGui::DragFloat("Bend damping", (float*)&mesh.bendDamping, 0.5f, 0.f, 100.f);
			}
		}

		t = "Autoreset simulation: " + std::to_string(resetTimer) + "s";
		ImGui::Checkbox(t.c_str(), &autoReset);

		if (autoReset) ImGui::DragFloat("Autoreset timer", (float*)&resetTimer, 0.05f, 5.f, 10.f);

		if (ImGui::Button("Reset simulation")) ResetSimulation();
	}
	ImGui::End();
}

void PhysicsInit()
{
	srand(static_cast<unsigned>(time(nullptr)));
	renderParticles = false;
	renderCloth = true;
	renderSphere = false;
	solver = Solver();
	euler = Euler();
	verlet = Verlet();
	mesh = Mesh(ClothMesh::numCols, ClothMesh::numRows, glm::vec3(-2.8, 9.5, 4), 0.5);
	Sphere::updateSphere(solver.sphere.c, solver.sphere.r);
	LilSpheres::particleCount = mesh.width * mesh.height;

	//renderCapsule = true;
	//ps = ParticleSystem(10000);
	//emitter = Emitter(Emitter::Type::FOUNTAIN);
	//Capsule::updateCapsule(euler.capsule.pos[0], euler.capsule.pos[1], euler.capsule.r);
}

void PhysicsUpdate(float dt)
{
	if (playSimulation)
	{
		timer += dt;
		for (int i = 0; i < 10; i++)
		{
			if (usingVerlet) verlet.Update(mesh, dt / 10);
			else euler.Update(mesh, dt / 10);
		}

		if (autoReset && timer >= resetTimer) ResetSimulation();
	}
	ClothMesh::updateClothMesh(&mesh.positions[0].x);
	Sphere::updateSphere(solver.sphere.c, solver.sphere.r);
	LilSpheres::updateParticles(0, mesh.width * mesh.height, &mesh.positions[0].x);

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