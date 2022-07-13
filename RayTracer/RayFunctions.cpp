#include "RayFunctions.h"

Ray reflectRay(HitData& hitData) {
	glm::vec3 norm = hitData.HitSurface->GetUnitSurfaceNormal(hitData);
	glm::vec3 d = glm::normalize(hitData.IntersectingRay.dir);
	glm::vec3 r = glm::normalize(d - 2 * (glm::dot(d, norm)) * norm);
	glm::vec3 p = hitData.HitSurface->GetIntersectionPoint(hitData);
	return Ray(p, r);
}