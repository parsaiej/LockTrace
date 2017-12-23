#include <iostream>
#include <fstream>
#include <random>

#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"

Vec3 Color(const Ray& _r, Hitable *_world, int _depth) {
	HitRecord record;
	if (_world->Hit(_r, 0.001, FLT_MAX, record)) {
		Ray scattered;
		Vec3 attenuation;
		if (_depth < 50 && record.material->Scatter(_r, record, attenuation, scattered)) {
			return attenuation * Color(scattered, _world, _depth + 1);
		} 
		else {
			return Vec3(0, 0, 0);
		}
	} 
	else {
		Vec3 unitDirection = unit_vector(_r.Direction());
		float t = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

int main() {

	int nx = 400;
	int ny = 200;
	int ns = 100;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	std::ofstream image;
	image.open("image.ppm");
	image << "P3\n" << nx << " " << ny << "\n255\n";

	Hitable *list[4];
	list[0] = new Sphere(Vec3(0, 0, -1),      0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));
	list[2] = new Sphere(Vec3(1, 0, -1),      0.5, new Metal(Vec3(0.8, 0.6, 0.2)));
	list[3] = new Sphere(Vec3(-1, 0, -1),     0.5, new Metal(Vec3(0.8, 0.8, 0.8)));
	Hitable *world = new HitableList(list, 4);

	Camera cam;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			Vec3 c(0, 0, 0);
			
			for (int s = 0; s < ns; s++) {
				float u = float(i + dist(mt)) / float(nx);
				float v = float(j + dist(mt)) / float(ny);

				Ray r = cam.GetRay(u, v);
				c += Color(r, world, 0);
			}
			c /= float(ns);
			c = Vec3(sqrt(c[0]), sqrt(c[1]), sqrt(c[2]));

			int ir = int(255.99 * c[0]);
			int ig = int(255.99 * c[1]);
			int ib = int(255.99 * c[2]);
			image << ir << " " << ig << " " << ib << "\n";
		}
	}
	image.close();
}