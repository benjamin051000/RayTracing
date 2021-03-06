#pragma once
#include <math.h>
#include <iostream>


struct vec3 {
	//Constructors
	vec3() : e{ 0,0,0 } {}
	//vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

	//Coord getters
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	//General operator overloading
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; } // Not const because the reference will allow changes

	//Assignment operator overloading
	vec3& operator+=(const vec3& rhs);
	vec3& operator-=(const vec3& rhs);
	vec3& operator*=(const vec3& rhs);
	vec3& operator/=(const vec3& rhs);

	//Multiply by scalar
	vec3& operator*=(const double t);
	vec3& operator/=(const double t);

	double length() const { return sqrt(length_squared()); }
	double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	void make_unit_vector();

	bool near_zero() const {
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	inline static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	//Stores coordinates
	double e[3];
};

// Type aliases for vec3
using point3 = vec3;
using color = vec3;

/*-----Addition/Subtraction operators-----*/
inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

/*-----Multiplication operators-----*/
inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v[0], t * v[1], t * v[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

/*-----Division operators-----*/
inline vec3 operator/(const vec3& v1, const vec3& v2) {
	return vec3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

inline vec3 operator/(vec3 v, double t) {
	return (1/t) * v;
}

/*-----Assignment operators-----*/
inline vec3& vec3::operator+=(const vec3& rhs) {
	e[0] += rhs[0];
	e[1] += rhs[1];
	e[2] += rhs[2];
	return *this;
}

inline vec3& vec3::operator-=(const vec3& rhs) {
	e[0] -= rhs[0];
	e[1] -= rhs[1];
	e[2] -= rhs[2];
	return *this;
}

inline vec3& vec3::operator*=(const vec3& rhs) {
	e[0] *= rhs[0];
	e[1] *= rhs[1];
	e[2] *= rhs[2];
	return *this;
}

inline vec3& vec3::operator/=(const vec3& rhs) {
	e[0] /= rhs[0];
	e[1] /= rhs[1];
	e[2] /= rhs[2];
	return *this;
}

//Scalar assignments
inline vec3& vec3::operator*=(const double t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline vec3& vec3::operator/=(const double t) {
	return *this *= 1 / t;
}

//Miscellaneous operators
inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

inline float dot(const vec3& u, const vec3& v) {
	return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(
		u[1] * v[2] - u[2] * v[1],
		u[2] * v[0] - u[0] * v[2],
		u[0] * v[1] - u[1] * v[0]
	);
}

//inline void vec3::make_unit_vector() {
//	// This was deprecated in new RTIAW example code.
//	float k = 1.f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
//	e[0] *= k;
//	e[1] *= k;
//	e[2] *= k;
//}

//Output
inline std::ostream& operator<<(std::ostream& output, vec3& t) {
	return output << t[0] << " " << t[1] << " " << t[2];
}

/*----------Random Vector Generators----------*/
inline vec3 random_in_unit_disk() {
	while (true) {
		vec3 p(random_double(-1, 1), random_double(-1, 1), 0);
		
		if (p.length_squared() < 1)  return p;
	}
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		vec3 p = vec3::random(-1, 1);

		if (p.length_squared() < 1) return p;
	}
}

inline vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(1.0 - r_out_perp.length_squared()) * n;

	return r_out_parallel + r_out_perp;
}