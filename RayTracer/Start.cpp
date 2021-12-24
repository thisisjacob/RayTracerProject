#include "RayTracer.h";

int main() {
	RayTracer ray(800, 400, 0.0, 0.0, -5.0, 1.0);
	ray.Render();
}