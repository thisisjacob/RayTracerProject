#pragma once
#include "Ray.h"
#include "HitData.h"

class Surface {
	virtual bool IsHit(Ray ray, float t0, float t1, HitData& record);
};
