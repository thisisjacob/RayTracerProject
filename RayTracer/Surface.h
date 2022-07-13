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
	// Checks if an object is hit by the ray, and closer to the starting position
	// Returns a new HitData if this is the case
	// The passed record is returned if it is not
	virtual HitData IsHit(const std::shared_ptr<Surface>& callingSurface, Ray ray, float t0, float t1, const HitData& record) = 0;
	// Object for creating a bounding box of the given surface
	virtual BoundingBox boundingBox() const = 0;
	// Determines the pixel color value at the intersected point described by hitData
	// currRecurrDepth should be incremented when called within another call of the Color function
	// This argument is used to prevent infinite loops during reflection and refraction
	virtual glm::vec3 Color(HitData& hitData, WorldState& world, int currRecurrDepth = 0) = 0;
	// Returns the surface normal at the point intersected by hitData
	virtual glm::vec3 GetSurfaceNormal(HitData& hitData) = 0;
	// Returns the normalized surface normal at the point intersected by hitData
	virtual glm::vec3 GetUnitSurfaceNormal(HitData& hitData) = 0;
	// Gets the intersection point described by hitData
	virtual glm::vec3 GetIntersectionPoint(HitData& hitData) = 0;
};
