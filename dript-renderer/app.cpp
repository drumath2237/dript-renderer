#include <iostream>
#include <vector>

#include "ray.h"
#include "image.h"
#include "triangle.h"
#include "vec.h"
#include "intersect.h"
#include "scene.h"
#include "objFile.h"

using namespace std;

int main()
{
	ObjFile obj("./cube.obj");

	return 0;
}

int testfun()
{
	int width = 800;
	int height = 800;
	PPM ppm = PPM(width, height);

	Triangle tri1, tri2;
	tri1.v0 = Vec();
	tri1.v1 = Vec(0, 0.5, 0);
	tri1.v2 = Vec(0.5, 0, 0);

	tri2.v0 = Vec(-0.47, 0.61, 0);
	tri2.v1 = Vec(-.75, -.19, 0);
	tri2.v2 = Vec(-.33, 0.24, 0);

	Scene scene;
	scene.polygons.push_back(tri1);
	scene.polygons.push_back(tri2);

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

		Hit hit = scene.intersect(ray, 0.001, 100);
		if (hit.isHit) {
			Color.push_back(Vec(255, 0, 255));
		}
		else {
			Color.push_back(Vec());
		}
	}

	ppm_out(ppm, Color);

	return 0;

}