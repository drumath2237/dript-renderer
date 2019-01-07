#pragma once

#include <vector>

#include "vec.h"
#include "triangle.h"
#include "hit.h"
#include "intersect.h"
#include "ray.h"


struct Scene
{
	vector<Triangle> polygons;

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

		return rayhit;
	}
};
