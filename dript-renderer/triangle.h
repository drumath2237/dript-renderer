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

