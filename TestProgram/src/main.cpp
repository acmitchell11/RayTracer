#include "Scene.h"
#include "Camera.h"
#include "Objects/Sphere.h"
#include "Objects/Box.h"
#include "Objects/Mesh.h"
#include "Objects/MeshInstance.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "ConstMaterial.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Lights/BoxLight.h"
#include <time.h>
#include <iostream>

using namespace RayTracer;

int main(int argc, char* argv[])
{
	// Create the camera and create a scene with it
	Camera camera = RayTracer::Camera(640, 480, 45.0f, { 0,0.5,-1.5 }, { 0,0,-3 });
	Scene scene(camera);
	

	// Create the materials to be used in the scene
	ConstMaterial teapotMat1; teapotMat1.albedo = { 0.972, 0.960, 0.915 }; teapotMat1.emissiveness = { 0,0,0 }; teapotMat1.reflectiveness = 0.1f;
	ConstMaterial teapotMat2; teapotMat2.albedo = { 67.0f / 255.0f, 94.0f / 255.0f, 82.0f / 255.0f }; teapotMat2.emissiveness = { 0,0,0 }; teapotMat2.reflectiveness = 0.1f;
	ConstMaterial teapotMat3; teapotMat3.albedo = { 16.0f / 255.0f, 32.0f / 255.0f, 75.0f / 255.0f }; teapotMat3.emissiveness = { 0,0,0 }; teapotMat3.reflectiveness = 0.1f;
	ConstMaterial floorMat; floorMat.albedo = { 86.0f/255.0f,125.0f/255.0f,70.0f/255.0f }; floorMat.emissiveness = { 0.0f,0.0f,0.0f }; floorMat.reflectiveness = 0.0f;
	ConstMaterial backWallMat; backWallMat.albedo = { 0,0,1 }; backWallMat.emissiveness = { 0.0f,0.0f,0.0f }; backWallMat.reflectiveness = 0.0f;
	ConstMaterial areaLightMat; areaLightMat.albedo = { 1,1,1 }; areaLightMat.emissiveness = { 1,1,1 }; areaLightMat.reflectiveness = 0.0f;


	// Add area lights
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0, 1.48, -2 });
	BoxLight boxLight1 = BoxLight(transform, { 0.5,0.01,0.5 }, &areaLightMat, { 1,1,1 }, 5.0f);
	scene.AddLight(&boxLight1);

	transform = glm::translate(glm::mat4(1.0f), { 0, 1.5, -2 });
	Box fakeLight1 = Box(transform, &areaLightMat, { 0.5, 0.01, 0.5 });
	scene.AddObject(&fakeLight1);

	DirectionalLight sunLight = DirectionalLight({ -0.5,-1,-1 }, { 1,1,1 });
	//scene.AddLight(&sunLight);

	// Load the meshes for the scene
	Mesh teapotMesh = Mesh("teapot.obj", 11);
	Mesh bunnyMesh = Mesh("bunny_very_hi.obj", 15);

	/*transform = glm::translate(glm::mat4(1.0f), { 0, 0, -3 });
	transform = glm::rotate(transform, glm::radians(-90.0f), { 1,0,0 });
	transform = glm::rotate(transform, glm::radians(-35.0f), { 0,0,1 });
	transform = glm::scale(transform, { 0.025, 0.025, 0.025 });
	MeshInstance teapotInstance = MeshInstance(&teapotMesh, transform, &teapotMat1);
	scene.AddObject(&teapotInstance);*/

	transform = glm::translate(glm::mat4(1.0f), { 0.1, 0.05, -3 });
	//transform = glm::rotate(transform, glm::radians(-90.0f), { 1,0,0 });
	//transform = glm::rotate(transform, glm::radians(-35.0f), { 0,0,1 });
	transform = glm::scale(transform, { 0.2, 0.2, 0.2 });
	MeshInstance bunnyInstance = MeshInstance(&bunnyMesh, transform, &teapotMat1);
	scene.AddObject(&bunnyInstance);

	transform = glm::translate(glm::mat4(1.0f), { 0.75, 0, -3.75 });
	transform = glm::rotate(transform, glm::radians(-90.0f), { 1,0,0 });
	transform = glm::rotate(transform, glm::radians(-25.0f), { 0,0,1 });
	transform = glm::scale(transform, { 0.025, 0.025, 0.025 });
	MeshInstance teapotInstance2 = MeshInstance(&teapotMesh, transform, &teapotMat2);
	scene.AddObject(&teapotInstance2);

	transform = glm::translate(glm::mat4(1.0f), { -0.75, 0, -3.75 });
	transform = glm::rotate(transform, glm::radians(-90.0f), { 1,0,0 });
	transform = glm::rotate(transform, glm::radians(-155.0f), { 0,0,1 });
	transform = glm::scale(transform, { 0.025, 0.025, 0.025 });
	MeshInstance teapotInstance3 = MeshInstance(&teapotMesh, transform, &teapotMat3);
	scene.AddObject(&teapotInstance3);

	// Add the floor and ceiling
	transform = glm::translate(glm::mat4(1.0f), { 0,-0.025,-5 });
	Box floor = Box(transform, &floorMat, { 20,0.05,20 });
	scene.AddObject(&floor);

	transform = glm::translate(glm::mat4(1.0f), { 0, 3.025, -5 });
	Box ceiling = Box(transform, &backWallMat, { 20,0.05,20 });
	//scene.AddObject(&ceiling);

	// Add back wall
	transform = glm::translate(glm::mat4(1.0f), { 0,0,-15 });
	Box backWall = Box(transform, &backWallMat, { 20,20,0.05 });
	//scene.AddObject(&backWall);


	// Render and save the image. The image saves in the TestProgram folder (when I run the project that's where VS puts it at least)

	time_t startTime = time(0);
	scene.RenderScene();
	time_t endTime = time(0);

	time_t deltaTime = endTime - startTime;

	scene.SaveScene("TestImage.ppm");

	float hours = deltaTime / (60.0f * 60.0f);
	int wholeHours = int(hours);

	float minutes = (hours - wholeHours) * 60.0f;
	int wholeMinutes = int(minutes);

	float seconds = (minutes - wholeMinutes) * 60.0f;
	int wholeSeconds = int(seconds);


	std::cout << "Time to render: " << wholeHours << " hours, " << wholeMinutes << " minutes, " << wholeSeconds << " seconds." << std::endl;
	system("PAUSE");
}