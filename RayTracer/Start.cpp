#include "RayTracer.h";
#include "WorldState.h"
#include "Lambertian.h"
#include "BaseShader.h"

int main() {
	WorldState world;
	BlinnPhong* shader1 = new BlinnPhong();
	shader1->SetDiffuseCoeff(glm::tvec3<double>(0.7, 0.2, 0.2));
	shader1->SetAmbientCoeff(glm::tvec3<double>(0.7, 0.2, 0.2));
	shader1->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	BlinnPhong* shader2 = new BlinnPhong();
	shader2->SetDiffuseCoeff(glm::tvec3<double>(0.2, 0.2, 0.7));
	shader2->SetAmbientCoeff(glm::tvec3<double>(0.2, 0.2, 0.7));
	shader2->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	BlinnPhong* shader3 = new BlinnPhong();
	shader3->SetDiffuseCoeff(glm::tvec3<double>(0.2, 0.7, 0.2));
	shader3->SetAmbientCoeff(glm::tvec3<double>(0.2, 0.7, 0.2));
	shader3->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(0.0, 0.0, -1.0, 1.0, shader1)));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(-2.5, 0.0, 2.0, 1.0, shader2)));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(2.5, 0.0, -1.0, 1.0, shader3)));
	std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light{ glm::tvec3<double>(0.0, 0.0, 1.4), 5.0 });
	std::shared_ptr<Light> newLight = std::shared_ptr<Light>(new Light{ glm::tvec3<double>(2.0, 0.0, 1.0), 2.0 });
	world.AddLight(light);
	world.AddLight(newLight);
	Camera camera = Camera(800, 400, -1.0, 0.0, 5.0, 1.0);
	world.SetCamera(camera);
	RayTracer ray(world);
	ray.Render();

	return 0;
}
