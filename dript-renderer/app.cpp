#include <iostream>
#include <vector>

#include "ray.h"
#include "image.h"
#include "triangle.h"
#include "vec.h"

using namespace std;

int main()
{
	Triangle tri;
	tri.v0 = Vec();
	tri.v1 = Vec(1, 1, 0);
	tri.v2 = Vec(1, -1, 0);

	Ray ray;
	ray.o = Vec(0.5, 0, 5);
	ray.d = Vec(0, 0, -1);

	double t = intersect(tri, ray, 0.1, 100);
	cout << t << endl;
}