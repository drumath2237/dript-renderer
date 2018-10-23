#include <iostream>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

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
	Triangle* triangles = (Triangle*)rtcSetNewGeometryBuffer(mesh, RTC_BUFFER_TYPE_INDEX, 0, RTC_FORMAT_UINT3, sizeof(Triangle), 2);
	triangles[tri].v0 = 0; triangles[tri].v1 = 1; triangles[tri].v2 = 3; tri++; // ŽOŠpŒ`ABD
	triangles[tri].v0 = 1; triangles[tri].v1 = 2; triangles[tri].v2 = 3; tri++; // ŽOŠpŒ`BCD

	unsigned int geomID = rtcAttachGeometry(scene, mesh);

	RTCIntersectContext context;
	rtcInitIntersectContext(&context);
	RTCHit rtchit;
	rtchit.geomID = geomID;

	RTCRay rtcray;
	rtcray.org_x = 0.0;
	rtcray.org_y = 0.0;
	rtcray.org_z = 2.0;

	rtcray.dir_x = 0.0;
	rtcray.dir_y = 0.0;
	rtcray.dir_z = -1.0;

	rtcray.tnear = 0.0f;
	rtcray.tfar = INFINITY;
	rtcray.time = 0.0;

	RTCRayHit ray;
	rtcIntersect1(scene, &context, &ray);
	if (rtchit.geomID == RTC_INVALID_GEOMETRY_ID)
	{
		cout << "invalid intersection" << endl;
	}
	else {
		cout << "intersected" << endl;
	}

	/*  Release process */
	rtcReleaseScene(scene);
	rtcReleaseDevice(device);

	char n;
	cin >> n;

	return 0;
}