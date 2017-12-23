#ifndef MATERIALH
#define MATERIALH

#include <random>
#include "Hitable.h"

Vec3 Reflect(const Vec3& _V, const Vec3& _N) {
	return _V - 2 * dot(_V, _N) * _N;
}

Vec3 RandomInUnitSphere() {

	std::random_device dev;
	std::mt19937 mt(dev());
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	Vec3 p;
	do {
		p = 2.0 * Vec3(dist(mt), dist(mt), dist(mt)) - Vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

class Material {
public:
	virtual bool Scatter(const Ray& _rIn, const HitRecord& _record, Vec3& _attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
	Lambertian(const Vec3& _a) : albedo(_a) {}
	virtual bool Scatter(const Ray& _rIn, const HitRecord& _record, Vec3& _attenuation, Ray& _scattered) const {
		Vec3 target = _record.p + _record.normal + RandomInUnitSphere();
		_scattered   = Ray(_record.p, target - _record.p);
		_attenuation = albedo;
		return true;
	}

	Vec3 albedo;
};

class Metal : public Material {
public:
	Metal(const Vec3& _a) : albedo(_a) {}
	virtual bool Scatter(const Ray& _rIn, const HitRecord& _record, Vec3& _attenuation, Ray& _scattered) const {
		Vec3 reflected = Reflect(unit_vector(_rIn.Direction()), _record.normal);
		_scattered = Ray(_record.p, reflected);
		_attenuation = albedo;
		return (dot(_scattered.Direction(), _record.normal) > 0);
	}

	Vec3 albedo;
};

#endif