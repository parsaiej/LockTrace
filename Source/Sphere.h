#ifndef SPHEREH
#define SPHEREH

#include "Hitable.h"

class Sphere : public Hitable {
public:
	Sphere() {}
	Sphere(Vec3 _center, float _r, Material *_m) : center(_center), radius(_r), material(_m) {};

	virtual bool Hit(const Ray& _r, float _tMin, float _tMax, HitRecord& _record) const;

	Vec3      center;
	float     radius;
	Material *material;
};

bool Sphere::Hit(const Ray& _r, float _tMin, float _tMax, HitRecord& _record) const {
	Vec3 oc = _r.Origin() - center;
	float a = dot(_r.Direction(), _r.Direction());
	float b = dot(oc, _r.Direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;


	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < _tMax && temp > _tMin) {
			_record.t = temp;
			_record.p = _r.PointAtParameter(_record.t);
			_record.normal = (_record.p - center) / radius;
			_record.material = material;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if (temp < _tMax && temp > _tMin) {
			_record.t = temp;
			_record.p = _r.PointAtParameter(_record.t);
			_record.normal = (_record.p - center) / radius;
			_record.material = material;
			return true;
		}
	}
	return false;
}

#endif