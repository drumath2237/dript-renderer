#pragma once

#include "vec.h"
#include "triangle.h"

struct Hit
{
	bool isHit;
	double t;
	Triangle* poly;
	Vec p;
};
