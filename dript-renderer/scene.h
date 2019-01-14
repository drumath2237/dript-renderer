#pragma once

#include <vector>
#include <algorithm>

#include "vec.h"
#include "triangle.h"
#include "hit.h"
#include "intersect.h"
#include "ray.h"
#include "light.h"


struct Scene
{
	vector<Triangle> polygons;
	Light light;

	Hit intersect(Ray ray, double tmin, double tmax) {
		Hit rayhit;
		rayhit.t = tmax;
		rayhit.isHit = false;

		for (auto poly : polygons) {

			Hit tmpHit = isRayIntersectPolygon(poly, ray, tmin, tmax);
			if (tmpHit.isHit) {
				if (tmpHit.t < rayhit.t) {
					rayhit = tmpHit;
				}
			}

		}

		rayhit.p = ray.o + ray.d*rayhit.t;

		return rayhit;
	}

	Vec radiance(Ray ray)
	{
		Hit hit = intersect(ray, 0.001, 100);
		if (!hit.isHit)
			return Vec();

		Vec ldir = light.pos - hit.p;
		double len = length(ldir);

		Ray ray_;
		ray_.o = hit.p;
		ray_.d = normalize(ldir);

		Hit hit_ = intersect(ray_, 0.00001, 100);

		if (hit_.t >= len) {
			Vec orienting_normal = dot(hit.poly->normal, ray.d) < 0.0 ? hit.poly->normal : hit.poly->normal * -1.0;
			return std::max(0.0, dot(orienting_normal, ldir / len)) * multiply(light.color, Vec(200, 200, 200)) / (len*len);
		}
		else {
			return Vec();
		}
		
	}
};
