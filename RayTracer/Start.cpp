#include "RayTracer.h";
#include "WorldState.h"
#include "Lambertian.h"

int main() {
	WorldState world;
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(0.0, 0.0, -1.0, 1.0, new Lambertian(glm::vec3(0.7, 0.2, 0.2)))));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(-2.5, 0.0, 2.0, 1.0, new Lambertian(glm::vec3(0.2, 0.2, 0.7)))));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(2.5, 0.0, -1.0, 1.0, new Lambertian(glm::vec3(0.2, 0.7, 0.2)))));
	std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light{ glm::vec3(0.0, 0.0, 1.4), 5.0 });
	std::shared_ptr<Light> newLight = std::shared_ptr<Light>(new Light{ glm::vec3(2.0, 0.0, 1.0), 2.0 });
	world.AddLight(light);
	world.AddLight(newLight);
	RayTracer ray(800, 400, 0.0, 0.0, 5.0, 1.0, world);
	ray.Render();

	return 0;
}
