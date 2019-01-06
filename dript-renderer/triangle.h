#pragma once

#include "vec.h"
#include "ray.h"

struct Triangle
{
	Vec v0, v1, v2;
	Vec normal;

	Triangle() {};
	Triangle(Vec v0, Vec v1, Vec v2) : v0(v0), v1(v1), v2(v2) {};
	Triangle(Vec v0, Vec v1, Vec v2, Vec normal_) : v0(v0), v1(v1), v2(v2), normal(normal_) {};
};

double intersect(Triangle polygon, Ray ray, double tmin, double tmax)
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

	double beta = result_of_cramer.y;
	double gamma = result_of_cramer.z;

	// ��������->�����_p�̓�������
	if (beta>0 && gamma>0 && beta+gamma<1)
	{
		return result_of_cramer.x;
	}
	else
	{
		return -1;
	}
}
