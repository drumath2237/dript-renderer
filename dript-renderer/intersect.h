#pragma once

#include "vec.h"
#include "triangle.h"
#include "hit.h"

Hit isRayIntersectPolygon(Triangle polygon, Ray ray, double tmin, double tmax)
{
	Vec v0 = polygon.v0;
	Vec v1 = polygon.v1;
	Vec v2 = polygon.v2;

	Vec e1 = v1 - v0;
	Vec e2 = v2 - v0;
	Vec r = ray.o - v0;

	Vec u = cross(ray.d, e2);
	Vec v = cross(r, e1);

	// �N�������̌�����p����(t, beta, gamma)���Z�o�������ʂ̃x�N�g��
	Vec result_of_cramer = Vec(dot(v, e2), dot(u, r), dot(v, ray.d)) / dot(u, e1);

	double t = result_of_cramer.x;
	double beta = result_of_cramer.y;
	double gamma = result_of_cramer.z;

	// ��������->�����_p�̓�������
	if (beta > 0 && gamma > 0 && beta + gamma < 1)
	{
		Hit hit;
		hit.isHit = true;
		hit.t = result_of_cramer.x;
		hit.poly = &polygon;
		hit.p = ray.o + ray.d * result_of_cramer.x;
		return hit;
	}
	else
	{
		Hit hit;
		hit.isHit = false;
		return hit;
	}
}
