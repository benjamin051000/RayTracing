#include <iostream>
#include <fstream>
#include "hittable_list.h"
#include "sphere.h"
#include "float.h"

vec3 color(const ray &r, hittable *world) {
	hit_record rec;
	if (world->hit(r, 0, FLT_MAX, rec)) {
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5 * (unit_dir.y() + 1);
		return (1.0 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1);
	}
}

int main() {
	int nx = 200;
	int ny = 100;
	
	std::ofstream out("image.ppm");
	
	out << "P3\n" << nx << " " << ny << "\n255\n";
	
	const vec3 lower_left_corner(-2, -1, -1);
	const vec3 horizontal(4, 0, 0);
	const vec3 vertical(0, 2, 0);
	const vec3 origin(0, 0, 0);
	
	hittable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hittable *world = new hittable_list(list, 2);

	//Iterate through each pixel
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			
			vec3 col = color(r, world);
			int ir = int(255.99 * col[0]),
				ig = int(255.99 * col[1]),
				ib = int(255.99 * col[2]);
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
}