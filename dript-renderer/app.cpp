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
	cout << "rendering started!" << endl;

	int width = 400;
	int height = 400;
	PPM ppm = PPM(width, height);

	ObjFile obj("./cube.obj");

	Scene scene;

	for (auto poly : obj.polys) {
		scene.polygons.push_back(poly);
	}

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
			//Vec col = normalize(hit.poly->normal);
			//Vec newcol = Vec(abs(col.x), abs(col.y), abs(col.z));
			//Color.push_back(newcol*255);
			Color.push_back(Vec(255, 0, 255));
		}
		else {
			Color.push_back(Vec());
		}
	}

	ppm_out(ppm, Color);

	return 0;

}