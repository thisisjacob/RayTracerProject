#include "RayTracer.h";
#include "WorldState.h"
#include "BaseShader.h"

int main() {
	WorldState world;
	BlinnPhong* shader1 = new BlinnPhong();
	shader1->SetDiffuseCoeff(glm::tvec3<double>(0.7, 0.2, 0.2));
	shader1->SetAmbientCoeff(glm::tvec3<double>(0.7, 0.2, 0.2));
	shader1->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	shader1->SetSpecularCoeff(glm::tvec3<double>(0.3, 0.3, 0.3));
	shader1->SetPhongExponent(16.0);
	BlinnPhong* shader2 = new BlinnPhong();
	shader2->SetDiffuseCoeff(glm::tvec3<double>(0.2, 0.2, 0.7));
	shader2->SetAmbientCoeff(glm::tvec3<double>(0.2, 0.2, 0.7));
	shader2->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	shader2->SetSpecularCoeff(glm::tvec3<double>(0.5, 0.5, 0.5));
	shader2->SetPhongExponent(16.0);
	BlinnPhong* shader3 = new BlinnPhong();
	shader3->SetDiffuseCoeff(glm::tvec3<double>(0.2, 0.7, 0.2));
	shader3->SetAmbientCoeff(glm::tvec3<double>(0.2, 0.7, 0.2));
	shader3->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	shader3->SetSpecularCoeff(glm::tvec3<double>(0.5, 0.5, 0.5));
	shader3->SetPhongExponent(16.0);
	BlinnPhong* grassShader = new BlinnPhong();
	grassShader->SetDiffuseCoeff(glm::tvec3<double>(0.0, 0.1, 0.0));
	grassShader->SetAmbientCoeff(glm::tvec3<double>(0.1, 0.6, 0.1));
	grassShader->SetAmbientIntensity(glm::tvec3<double>(0.1, 0.5, 0.1));
	grassShader->SetSpecularCoeff(glm::tvec3<double>(0.0, 0.0, 0.0));
	grassShader->SetPhongExponent(1.0);
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(0.0, 0.0, -1.0, 1.0, shader1)));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(-2.5, 0.0, 2.0, 1.0, shader2)));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(2.5, 0.0, -1.0, 1.0, shader3)));
	world.AddSurface(std::shared_ptr<Surface>(new Sphere(0.0, -10.0, 0.0, 9, grassShader)));
	std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light{ glm::tvec3<double>(-1.5, 0.0, 3.2), glm::tvec3<double>(0.5, 0.5, 0.5) });
	std::shared_ptr<Light> newLight = std::shared_ptr<Light>(new Light{ glm::tvec3<double>(0.0, -0.8, 0.5), glm::tvec3<double>(0.5, 0.5, 0.5) });
	std::shared_ptr<Light> backLight = std::shared_ptr<Light>(new Light{ glm::tvec3<double>(0.0, 0.0, -3.0), glm::tvec3<double>(0.5, 0.5, 0.5) });
	world.AddLight(light);
	world.AddLight(newLight);
	//world.AddLight(backLight);
	Camera camera = Camera(800, 400, -1.0, 0.0, 5.0, 1.0);
	world.SetCamera(camera);
	RayTracer ray(world);
	ray.Render();

	return 0;
}
