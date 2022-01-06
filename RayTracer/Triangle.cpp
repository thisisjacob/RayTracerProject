#include "Triangle.h"

Triangle::Triangle(glm::tvec3<double> aVert, glm::tvec3<double> bVert, glm::tvec3<double> cVert, const std::shared_ptr<Material>& mat) {
	aVertex = glm::tvec3<double>(aVert);
	bVertex = glm::tvec3<double>(bVert);
	cVertex = glm::tvec3<double>(cVert);
	this->mat = mat;
}

bool Triangle::IsHit(Ray ray, double t0, double t1, HitData& record) {
	glm::tmat3x3<double> A;
	A[0] = glm::tvec3<double>(aVertex.x - bVertex.x, aVertex.x - cVertex.x, ray.dir.x);
	A[1] = glm::tvec3<double>(aVertex.y - bVertex.y, aVertex.y - cVertex.y, ray.dir.y);
	A[2] = glm::tvec3<double>(aVertex.z - bVertex.z, aVertex.z - cVertex.z, ray.dir.z);
	double eiMinHf = A[1][1] * A[2][2] - A[1][2] * A[2][1];
	double gfMinDi = A[0][2] * A[2][1] - A[0][1] * A[2][2];
	double dhMinEg = A[0][1] * A[1][2] - A[1][1] * A[0][2];
	double j = aVertex.x - ray.origin.x;
	double k = aVertex.y - ray.origin.y;
	double l = aVertex.z - ray.origin.z;
	double M = A[0][0] * eiMinHf + A[1][0] * gfMinDi + A[2][0] * dhMinEg;
	double t = -(A[2][1] * (A[0][0] * k - j * A[1][0]) + A[1][1] * (j * A[2][0] - A[0][0] * l) + A[0][1] * (A[1][0] * l - k * A[2][0])) / M;
	if (t < t0 || t > t1)
		return false;
	double gamma = (A[2][2] * (A[0][0] * k - j * A[1][0]) + A[1][2] * (j * A[2][0] - A[0][0] * l) + A[0][2] * (A[1][0] * l - k * A[2][0])) / M;
	if (gamma < 0.0 || gamma > 1.0)
		return false;
	double beta = (j * eiMinHf + k * gfMinDi + l * dhMinEg) / M;
	if (beta < 0.0 || beta > 1 - gamma)
		return false;
	record.T = t;
	record.IsHit = true;
};

glm::tvec3<double> Triangle::Color(HitData& hitData, WorldState& world) {
	return mat->Shading(hitData, world);
}

glm::tvec3<double> Triangle::GetSurfaceNormal(HitData& hitData) {
	glm::tvec3<double> a = bVertex - aVertex;
	glm::tvec3<double> b = cVertex - aVertex;
	return glm::cross(a, b);
}

glm::tvec3<double> Triangle::GetUnitSurfaceNormal(HitData& hitData) {
	return glm::normalize(GetSurfaceNormal(hitData));
}

glm::tvec3<double> Triangle::GetIntersectionPoint(HitData& hitData) {
	glm::tvec3<double> p = glm::tvec3<double>(hitData.IntersectingRay.dir);
	p *= hitData.T;
	p += hitData.IntersectingRay.origin;
	return p;
}