#include <iostream>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "image.h"

#define MY_INVALID_GEOM_ID 3435973836

using namespace std;

int main()
{
	cout << "start project" << endl;

	RTCDevice device = rtcNewDevice(NULL);
	RTCScene scene = rtcNewScene(device);

	struct Vertex { float x, y, z; };
	struct Triangle { int v0, v1, v2; };

	RTCGeometry mesh = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

	Vertex* vertices = (Vertex*)rtcSetNewGeometryBuffer(mesh, RTC_BUFFER_TYPE_VERTEX, 0, RTC_FORMAT_FLOAT3, sizeof(Vertex), 4);
	vertices[0].x = 1; vertices[0].y = 1; vertices[0].z = 0;
	vertices[1].x = 1; vertices[1].y = -1; vertices[1].z = 0;
	vertices[2].x = -1; vertices[2].y = 1; vertices[2].z = 0;
	vertices[3].x = -1; vertices[3].y = -1; vertices[3].z = 0;

	int tri = 0;
	Triangle* triangles = (Triangle*)rtcSetNewGeometryBuffer(mesh, RTC_BUFFER_TYPE_INDEX, 0, RTC_FORMAT_UINT3, sizeof(Triangle), 1);
	triangles[tri].v0 = 0; triangles[tri].v1 = 1; triangles[tri].v2 = 2; tri++;
	//triangles[tri].v0 = 1; triangles[tri].v1 = 2; triangles[tri].v2 = 3; tri++;

	rtcCommitGeometry(mesh);

	unsigned int geomID = rtcAttachGeometry(scene, mesh); // attatch geometry(mesh) to scene.

	rtcCommitScene(scene);

	RTCIntersectContext context;
	rtcInitIntersectContext(&context);

	RTCRayHit ray;

	ray.ray.org_x = -0.5;
	ray.ray.org_y = 0.5;
	ray.ray.org_z = 2.0;

	ray.ray.dir_x = 0.0;
	ray.ray.dir_y = 0.0;
	ray.ray.dir_z = -1.0;

	ray.ray.tnear = 0.0f;
	ray.ray.tfar = INFINITY;
	ray.ray.time = 0.0;

	rtcIntersect1(scene, &context, &ray);
	cout << ray.hit.geomID << endl;

	Vec v = Vec(
		ray.hit.Ng_x,
		ray.hit.Ng_y,
		ray.hit.Ng_z
	);
	showVec(normalize(v));

	if (ray.hit.geomID == MY_INVALID_GEOM_ID)
	{
		cout << "invalid intersection" << endl;
	}
	else {
		cout << "intersected" << endl;
	}

	/*  Release process */
	rtcReleaseScene(scene);
	rtcReleaseDevice(device);

	return 0;
}