#include <iostream>

#include "vec.h"
#include "objFile.h"

using namespace std;

int main()
{
	ObjFile f("D:/kaito's file/metasequoia/cube.obj");
	for (auto v : f.normals) {
		cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
	}

	return 0;
}