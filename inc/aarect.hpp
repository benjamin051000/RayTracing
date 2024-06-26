#pragma once

#include "common.hpp"
#include "hittable.hpp"

class xy_rect : public hittable {
public:
	xy_rect() {}
	xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<material> mat) : mp(mat), x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box([[maybe_unused]] double time0, [[maybe_unused]] double time1, aabb& output_box) const override {
        // The bounding box must have non-zero width in each dimension, so pad the Z
        // dimension a small amount.
        output_box = aabb(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
        return true;
    }

	shared_ptr<material> mp;
	double x0 = 0, x1 = 0, y0 = 0, y1 = 0, k = 0;
};

class xz_rect : public hittable {
public:
	xz_rect() {}
    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,
        shared_ptr<material> mat)
        : mp(mat), x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k) {};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box([[maybe_unused]] double time0, [[maybe_unused]] double time1, aabb& output_box) const override {
        // The bounding box must have non-zero width in each dimension, so pad the Y
        // dimension a small amount.
        output_box = aabb(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
        return true;
    }


    shared_ptr<material> mp;
    double x0 = 0, x1 = 0, z0 = 0, z1 = 0, k = 0;
};

class yz_rect : public hittable {
public:
    yz_rect() {}

    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k,
        shared_ptr<material> mat)
        : mp(mat), y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k) {};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box([[maybe_unused]] double time0, [[maybe_unused]] double time1, aabb& output_box) const override {
        // The bounding box must have non-zero width in each dimension, so pad the X
        // dimension a small amount.
        output_box = aabb(point3(k - 0.0001, y0, z0), point3(k + 0.0001, y1, z1));
        return true;
    }

    shared_ptr<material> mp;
    double y0 = 0, y1 = 0, z0 = 0, z1 = 0, k = 0;
};
