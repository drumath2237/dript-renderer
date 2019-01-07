#include <iostream>
#include <vector>

#include "ray.h"
#include "image.h"
#include "triangle.h"
#include "vec.h"
#include "intersect.h"

using namespace std;

int main()
{
	int width = 800;
	int height = 800;
	PPM ppm = PPM(width, height);

	Triangle tri;
	tri.v0 = Vec(0, 0, 1);
	tri.v1 = Vec(1, 1, 0);
	tri.v2 = Vec(1, -1, 0);

	vector<Vec> Color = vector<Vec>();

	Ray ray;

	for (int i = 0; i < width*height; i++)
	{
		int w = i % height;
		int h = i / height;

		double x = (double)w / ((double)ppm.width / 2.) - 1.;
		double y = (double)h / ((double)ppm.height / 2.) - 1.;

		ray.o = Vec(x, y, 5);
		ray.d = Vec(0, 0, -1);

		//double t = intersect(tri, ray, 0.001, 100);
		Hit hit = isRayIntersectPolygon(tri, ray, 0.001, 100);
		double t = hit.t;
		if (t >= 0) {
			Color.push_back(Vec(255, 0, 255));
		}
		else {
			Color.push_back(Vec());
		}
	}

	ppm_out(ppm, Color);

}