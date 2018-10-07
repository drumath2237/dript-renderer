#include <iostream>

#include "vec.h"
#include "objFile.h"

using namespace std;

int main()
{
	ObjFile f("D:/kaitoFolder/blender/cube.obj");
	for (auto v : f.normals) {
		cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
	}
	cout << f.polys.size() << endl;

	return 0;
}