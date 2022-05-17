#pragma once
#include "Ray.h"
#include "HitData.h"
#include "Material.h"
#include "BoundingBox.h"
#include <memory>

struct HitData;
class WorldState;
class Material;

class Surface {
public:
	std::shared_ptr<Material> mat;
	virtual bool IsHit(Ray ray, float t0, float t1, HitData& record) = 0;
	virtual BoundingBox boundingBox() const = 0;
	virtual glm::vec3 Color(HitData& hitData, WorldState& world) = 0;
	virtual glm::vec3 GetSurfaceNormal(HitData& hitData) = 0;
	virtual glm::vec3 GetUnitSurfaceNormal(HitData& hitData) = 0;
	virtual glm::vec3 GetIntersectionPoint(HitData& hitData) = 0;
};
