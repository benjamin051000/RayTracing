#pragma once

#include "common.hpp"
#include "hittable_list.hpp"

class box : public hittable {
public:
	box() {}
	box(const point3& p0, const point3& p1, shared_ptr<material> material);

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
	
	virtual bool bounding_box([[maybe_unused]] double time0, [[maybe_unused]] double time1, aabb& output_box) const override {
		output_box = aabb(box_min, box_max);
		return true;
	}

	point3 box_min, box_max;
	hittable_list sides;
};

