#include "RayTracer.h";

int main() {
	RayTracer ray(400, 400, 0.0, 0.0, 1.0, 0.5);
	ray.Render();
}