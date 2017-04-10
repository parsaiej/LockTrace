#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

class vec3 {
public:
	vec3() {}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3		   operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float       operator[](int i) const { return e[i]; }
	inline float&      operator[](int i) { return e[i]; }

	inline vec3& operator+=(const vec3 &rhs);
	inline vec3& operator-=(const vec3 &rhs);
	inline vec3& operator*=(const vec3 &rhs);
	inline vec3& operator/=(const vec3 &rhs);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length()    const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float sprLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];	   }
	inline void normalize();
		

	float e[3];
};

int main() {

	int nx = 200;
	int ny = 100;

	std::ofstream image;
	image.open("image.ppm");
	image << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;

			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			image << ir << " " << ig << " " << ib << "\n";
		}
	}
	image.close();

}