#include "Triangle.h"

Triangle::Triangle(glm::vec3 aVert, glm::vec3 bVert, glm::vec3 cVert, const std::shared_ptr<Material>& mat) {
	aVertex = glm::vec3(aVert);
	bVertex = glm::vec3(bVert);
	cVertex = glm::vec3(cVert);
	this->mat = mat;
}

bool Triangle::IsHit(const std::shared_ptr<Surface>& callingSurface, Ray ray, float t0, float t1, HitData& record) {
	// Checks for if the triangle is degenerate, to prevent hits on it
	if ((aVertex == bVertex) || (aVertex == cVertex) || (cVertex == bVertex)) { return false; }

	glm::mat3x3 A;
	A[0] = glm::vec3(aVertex.x - bVertex.x, aVertex.x - cVertex.x, ray.dir.x);
	A[1] = glm::vec3(aVertex.y - bVertex.y, aVertex.y - cVertex.y, ray.dir.y);
	A[2] = glm::vec3(aVertex.z - bVertex.z, aVertex.z - cVertex.z, ray.dir.z);
	float eiMinHf = A[1][1] * A[2][2] - A[1][2] * A[2][1];
	float gfMinDi = A[0][2] * A[2][1] - A[0][1] * A[2][2];
	float dhMinEg = A[0][1] * A[1][2] - A[1][1] * A[0][2];
	float j = aVertex.x - ray.origin.x;
	float k = aVertex.y - ray.origin.y;
	float l = aVertex.z - ray.origin.z;
	float M = A[0][0] * eiMinHf + A[1][0] * gfMinDi + A[2][0] * dhMinEg;
	float t = -(A[2][1] * (A[0][0] * k - j * A[1][0]) + A[1][1] * (j * A[2][0] - A[0][0] * l) + A[0][1] * (A[1][0] * l - k * A[2][0])) / M;
	if (t < t0 || t > t1)
		return false;
	float gamma = (A[2][2] * (A[0][0] * k - j * A[1][0]) + A[1][2] * (j * A[2][0] - A[0][0] * l) + A[0][2] * (A[1][0] * l - k * A[2][0])) / M;
	if (gamma < 0.0 || gamma > 1.0)
		return false;
	float beta = (j * eiMinHf + k * gfMinDi + l * dhMinEg) / M;
	if (beta < 0.0 || beta > 1 - gamma)
		return false;
	record.T = t;
	record.IsHit = true;
	record.HitSurface = callingSurface;
	return true;
};

BoundingBox Triangle::boundingBox() const {
	float xMin = std::min({ aVertex.x, bVertex.x, cVertex.x });
	float yMin = std::min({ aVertex.y, bVertex.y, cVertex.y });
	float zMin = std::min({ aVertex.z, bVertex.z, cVertex.z });
	float xMax = std::max({ aVertex.x, bVertex.x, cVertex.x });
	float yMax = std::max({ aVertex.y, bVertex.y, cVertex.y });
	float zMax = std::max({ aVertex.z, bVertex.z, cVertex.z });

	return BoundingBox(glm::vec3(xMin, yMin, zMin), glm::vec3(xMax, yMax, zMax));
}

glm::vec3 Triangle::Color(HitData& hitData, WorldState& world) {
	return mat->Shading(hitData, world);
}

glm::vec3 Triangle::GetSurfaceNormal(HitData& hitData) {
	glm::vec3 a = bVertex - aVertex;
	glm::vec3 b = cVertex - aVertex;
	return glm::cross(a, b);
}

glm::vec3 Triangle::GetUnitSurfaceNormal(HitData& hitData) {
	return glm::normalize(GetSurfaceNormal(hitData));
}

glm::vec3 Triangle::GetIntersectionPoint(HitData& hitData) {
	glm::vec3 p = glm::vec3(hitData.IntersectingRay.dir);
	p *= hitData.T;
	p += hitData.IntersectingRay.origin;
	return p;
}