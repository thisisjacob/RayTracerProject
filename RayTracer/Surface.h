#pragma once
#include "Ray.h"
#include "HitData.h"

struct HitData;
class WorldState;

class Surface {
public:
	virtual bool IsHit(Ray ray, double t0, double t1, HitData& record) = 0;
	virtual glm::tvec3<double> Color(HitData& hitData, WorldState& world) = 0;
	virtual glm::tvec3<double> GetSurfaceNormal(HitData& hitData) = 0;
	virtual glm::tvec3<double> GetIntersectionPoint(HitData& hitData) = 0;
};
