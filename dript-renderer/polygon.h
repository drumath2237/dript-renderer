#pragma once
#include "vec.h"

struct Polygon3
{
	// members
	Vec a, b, c;

	// constructor
	Polygon3(Vec v):a(v),b(v),c(v){}
	Polygon3(Vec v1, Vec v2, Vec v3): a(v1),b(v2), c(v3){}
};