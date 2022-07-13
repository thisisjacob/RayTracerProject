#include "Application.h"

Application::Application() : world{}, rt{ } { }

bool Application::loadState(WorldState worldState) {
	return false;
}

bool Application::loadState(std::string filePath) {
	return false;
}

bool Application::loadTestState() {
	world.SetCamera(Camera(800, 600, glm::vec3(0.0, 0.0, 10.5), glm::vec3(0.0, 0.0, -1.0), 1.0));
	world.setRefractiveIndex(1.0);
	world.setBackgroundColor(glm::vec3(0.207, 0.318, 0.361));
	shared_ptr<Material> shader1 = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetDiffuseCoeff(glm::vec3(0.7, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetAmbientCoeff(glm::vec3(0.7, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetAmbientIntensity(glm::vec3(0.2, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetSpecularCoeff(glm::vec3(0.3, 0.3, 0.3));
	dynamic_pointer_cast<BlinnPhong>(shader1)->SetPhongExponent(16.0);
	shared_ptr<Material> shader2 = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetDiffuseCoeff(glm::vec3(0.2, 0.2, 0.7));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetAmbientCoeff(glm::vec3(0.2, 0.2, 0.7));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetAmbientIntensity(glm::vec3(0.2, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetSpecularCoeff(glm::vec3(0.5, 0.5, 0.5));
	dynamic_pointer_cast<BlinnPhong>(shader2)->SetPhongExponent(16.0);
	shared_ptr<Material> shader3 = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetDiffuseCoeff(glm::vec3(0.2, 0.7, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetAmbientCoeff(glm::vec3(0.2, 0.7, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetAmbientIntensity(glm::vec3(0.2, 0.2, 0.2));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetSpecularCoeff(glm::vec3(0.5, 0.5, 0.5));
	dynamic_pointer_cast<BlinnPhong>(shader3)->SetPhongExponent(16.0);
	shared_ptr<Material> grassShader = make_shared<BlinnPhong>();
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetDiffuseCoeff(glm::vec3(0.0, 0.1, 0.0));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetAmbientCoeff(glm::vec3(0.1, 0.6, 0.1));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetAmbientIntensity(glm::vec3(0.1, 0.5, 0.1));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetSpecularCoeff(glm::vec3(0.0, 0.0, 0.0));
	dynamic_pointer_cast<BlinnPhong>(grassShader)->SetPhongExponent(1.0);
	shared_ptr<Material> mirrorShader = make_shared<IdealSpecular>();
	dynamic_pointer_cast<IdealSpecular>(mirrorShader)->SetSpecularCoeff(glm::vec3(0.7, 0.7, 0.7));
	dynamic_pointer_cast<IdealSpecular>(mirrorShader)->SetAmbientCoeff(glm::vec3(0.0, 0.0, 0.0));
	dynamic_pointer_cast<IdealSpecular>(mirrorShader)->SetDiffuseCoeff(glm::vec3(0.6, 0.6, 0.6));
	shared_ptr<Material> refractShader = make_shared<RefractionShader>(1.5);
	world.AddSurface(shared_ptr<Surface>(new Sphere(0.2, 0.0, -1.0, 0.3, shader1)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(-2.0, 0.0, 5.0, 1.0, shader2)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(2.5, 0.0, 5.0, 1.0, shader3)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(0.0, -10.0, 0.0, 9, mirrorShader)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(4.0, 1.0, 0.0, 1.0, mirrorShader)));
	world.AddSurface(shared_ptr<Surface>(new Triangle(glm::vec3(-3.0, 2.0, -5.0),
		glm::vec3(3.0, 2.0, -4.0),
		glm::vec3(3.5, 5.0, -4.0),
		shader1)));
	world.AddSurface(shared_ptr<Surface>(new Sphere(0.0, 0.0, 4.0, 1.0, refractShader)));
	//world.AddSurface(shared_ptr<Surface>(new Model("./teapot.fbx", shader2)));

	shared_ptr<Light> light = shared_ptr<Light>(new Light{ glm::vec3(-1.5, 0.0, 4.2), glm::vec3(0.4, 0.4, 0.4) });
	shared_ptr<Light> newLight = shared_ptr<Light>(new Light{ glm::vec3(-4.0, 2.0, 0.5), glm::vec3(0.4, 0.4, 0.4) });
	shared_ptr<Light> backLight = shared_ptr<Light>(new Light{ glm::vec3(0.0, 0.0, 8.5), glm::vec3(0.6, 0.6, 0.6) });
	world.AddLight(light);
	world.AddLight(newLight);
	world.AddLight(backLight);
	return true;
}

void Application::startApplication() {
	rt.setWorld(world);
	MainInterface interface(rt.image.getWidth(), rt.image.getHeight());
	// Thread render so it runs alongside user interface
	std::thread rtThread(&RayTracer::Render, &rt);
	// TODO: Crashes with 300x300+ sizes when startInterface is uncommented
	interface.startInterface(rt.image);
	rtThread.join();
}