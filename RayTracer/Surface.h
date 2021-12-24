#pragma once
#include "Ray.h"
#include "HitData.h"

struct HitData;

class Surface {
public:
	virtual bool IsHit(Ray ray, float t0, float t1, HitData& record) = 0;
	virtual glm::vec3 Color(HitData& hitData) = 0;
	virtual glm::vec3 GetSurfaceNormal(HitData& hitData) = 0;
	virtual glm::vec3 GetIntersectionPoint(HitData& hitData) = 0;
};
