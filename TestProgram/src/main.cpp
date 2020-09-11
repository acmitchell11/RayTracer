#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Box.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "ConstMaterial.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

int main(int argc, char* argv[])
{
	// Create the camera with 1080p resolution and create a scene with it
	RayTracer::Camera camera = RayTracer::Camera(1920,1080);
	RayTracer::Scene scene(camera);

	// Create the lights for the scene
	RayTracer::PointLight pointLight1 = RayTracer::PointLight({ 1,1,1 }, 10.0f, { 0,0.6,0 });
	RayTracer::PointLight pointLight2 = RayTracer::PointLight({ 1,1,1 }, 10.0f, { 0,0.6,-4 });
	RayTracer::SpotLight spotLight1 = RayTracer::SpotLight({ 1,1,1 }, 15.0f, {0,0,0}, { 0,0,-1 }, 15.0f, 20.0f);

	scene.AddLight(&pointLight1);
	scene.AddLight(&pointLight2);
	scene.AddLight(&spotLight1);

	// Create the materials that will be used in the scene
	RayTracer::ConstMaterial redMat, blueMat, whiteMat, goldMat, silverMat, copperMat, mirrorMat;
	redMat.albedo = { 1,0,0 }; redMat.reflectiveness = 0.0f;
	blueMat.albedo = { 0,0,1 }; blueMat.reflectiveness = 0.0f;
	whiteMat.albedo = { 1,1,1 }; whiteMat.reflectiveness = 0.0f;
	goldMat.albedo = { 1, 0.766, 0.336 }; goldMat.reflectiveness = 0.2f;
	silverMat.albedo = { 0.972, 0.960, 0.915 }; silverMat.reflectiveness = 0.1f;
	copperMat.albedo = { 0.955, 0.637, 0.538 }; copperMat.reflectiveness = 0.1f;
	mirrorMat.albedo = { 1,1,1 }; mirrorMat.reflectiveness = 0.8f;

	// Place 2 spheres in room
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1, -0.2, -4.5));

	RayTracer::Sphere leftSphere = RayTracer::Sphere(transform, &silverMat, 0.2f);
	
	scene.AddObject(&leftSphere);

	transform = glm::translate(glm::mat4(1.0f), glm::vec3(1, -0.2, -4.5));

	RayTracer::Sphere rightSphere = RayTracer::Sphere(transform, &copperMat, 0.2f);

	scene.AddObject(&rightSphere);

	// place reflective cube
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -4.5));	
	transform = glm::rotate(transform, glm::radians(15.0f), { 1,0,0 });
	transform = glm::rotate(transform, glm::radians(45.0f), { 0,1,0 });
	RayTracer::Box cube = RayTracer::Box(transform, &goldMat, glm::vec3(0.5, 0.5, 0.5));

	scene.AddObject(&cube);

	// Create Room
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.55, -2.3));
	RayTracer::Box floor = RayTracer::Box(transform, &whiteMat, glm::vec3(3, 0.1, 5.4));

	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.75f, -2.3));
	RayTracer::Box ceiling = RayTracer::Box(transform, &whiteMat, glm::vec3(3, 0.1, 5.4));

	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.2, -5));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1, 0, 0));
	RayTracer::Box backWall = RayTracer::Box(transform, &whiteMat, glm::vec3(3, 0.1, 1.5));

	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25, 0.2, -2.3));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0, 0, 1));
	RayTracer::Box leftWall = RayTracer::Box(transform, &blueMat, glm::vec3(3, 0.1, 5.4));

	transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.25, 0.2, -2.3));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0, 0, 1));
	RayTracer::Box rightWall = RayTracer::Box(transform, &redMat, glm::vec3(3, 0.1, 5.4));

	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.2, 0.5));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1, 0, 0));
	RayTracer::Box wall = RayTracer::Box(transform, &mirrorMat, glm::vec3(3, 0.1, 1.5));

	scene.AddObject(&floor);
	scene.AddObject(&ceiling);
	scene.AddObject(&backWall);
	scene.AddObject(&leftWall);
	scene.AddObject(&rightWall);
	scene.AddObject(&wall);

	// Render and save the image. The image saves in the TestProgram folder (when I run the project that's where VS puts it at least)
	scene.RenderScene();
	scene.SaveScene("TestImage.ppm");
}