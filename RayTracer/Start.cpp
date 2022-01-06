#include "RayTracer.h";
#include "WorldState.h"
#include "BaseShader.h"
#include "IdealSpecular.h"

using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

int main() {
	// TODO: Find way to simplify repeated castings / pointer creation
	WorldState world;
	shared_ptr<Material> shader1 = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetDiffuseCoeff(glm::tvec3<double>(0.7, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetAmbientCoeff(glm::tvec3<double>(0.7, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetSpecularCoeff(glm::tvec3<double>(0.3, 0.3, 0.3));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetPhongExponent(16.0);
	shared_ptr<Material> shader2 = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetDiffuseCoeff(glm::tvec3<double>(0.2, 0.2, 0.7));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetAmbientCoeff(glm::tvec3<double>(0.2, 0.2, 0.7));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetSpecularCoeff(glm::tvec3<double>(0.5, 0.5, 0.5));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetPhongExponent(16.0);
	shared_ptr<Material> shader3 = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetDiffuseCoeff(glm::tvec3<double>(0.2, 0.7, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetAmbientCoeff(glm::tvec3<double>(0.2, 0.7, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetAmbientIntensity(glm::tvec3<double>(0.2, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetSpecularCoeff(glm::tvec3<double>(0.5, 0.5, 0.5));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetPhongExponent(16.0);
	shared_ptr<Material> grassShader = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetDiffuseCoeff(glm::tvec3<double>(0.0, 0.1, 0.0));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetAmbientCoeff(glm::tvec3<double>(0.1, 0.6, 0.1));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetAmbientIntensity(glm::tvec3<double>(0.1, 0.5, 0.1));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetSpecularCoeff(glm::tvec3<double>(0.0, 0.0, 0.0));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetPhongExponent(1.0);
	shared_ptr<Material> mirrorShader = make_shared<IdealSpecular>();
	dynamic_pointer_cast<IdealSpecular>(mirrorShader)->SetSpecularCoeff(glm::tvec3<double>(0.5f, 0.5f, 0.5f));
	world.AddSurface(shared_ptr<Surface>(new Sphere(0.0, 0.0, -1.0, 1.0, shader1)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(-2.5, 0.0, 2.0, 1.0, shader2)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(2.5, 0.0, -1.0, 1.0, shader3)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(0.0, -10.0, 0.0, 9, mirrorShader)));
	world.AddSurface(shared_ptr<Surface>(new Triangle(glm::tvec3<double>(-3.0, 2.0, -5.0),
															glm::tvec3<double>(3.0, 2.0, -4.0),
															glm::tvec3<double>(3.5, 5.0, -4.0),
															shader1)));
	shared_ptr<Light> light = shared_ptr<Light>(new Light{ glm::tvec3<double>(-1.5, 0.0, 4.2), glm::tvec3<double>(0.4, 0.4, 0.4) });
	shared_ptr<Light> newLight = shared_ptr<Light>(new Light{ glm::tvec3<double>(-4.0, 2.0, 0.5), glm::tvec3<double>(0.4, 0.4, 0.4) });
	shared_ptr<Light> backLight = shared_ptr<Light>(new Light{ glm::tvec3<double>(0.0, 0.0, -3.0), glm::tvec3<double>(0.4, 0.4, 0.4) });
	world.AddLight(light);
	world.AddLight(newLight);
	world.AddLight(backLight);
	Camera camera = Camera(800, 400, -1.0, 0.0, 5.5, 1.0);
	world.SetCamera(camera);
	RayTracer ray(world);
	ray.Render();

	return 0;
}
