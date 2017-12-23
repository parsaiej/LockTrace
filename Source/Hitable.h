#ifndef HITABLEH
#define HITABLEH

#include "Ray.h"

class Material;

struct HitRecord {
	float     t;
	Vec3      p;
	Vec3	  normal;
	Material *material;
};

class Hitable {
public:
	virtual bool Hit(const Ray& _r, float _tMin, float _tMax, HitRecord& _record) const = 0;
};

#endif