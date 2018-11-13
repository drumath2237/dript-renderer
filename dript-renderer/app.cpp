﻿#include <iostream>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "image.h"
#include <vector>

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
	vertices[0].x = 0.5; vertices[0].y = 0.5; vertices[0].z = 0;
	vertices[1].x = .5; vertices[1].y = -.5; vertices[1].z = 0;
	vertices[2].x = -.5; vertices[2].y = .5; vertices[2].z = 0;
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
	double orgx = -1.;
	double orgy = -1.;

	ray.ray.dir_x = 0.0;
	ray.ray.dir_y = 0.0;
	ray.ray.dir_z = -1.0;

	ray.ray.tnear = 0.0f;
	ray.ray.tfar = INFINITY;
	ray.ray.time = 0.0;

	int width = 100;
	int height = 100;
	PPM image = PPM(width, height);
	vector<Vec> colors;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ray.ray.org_x = orgx;
			ray.ray.org_y = orgy;
			ray.ray.org_z = 2.0;

			rtcIntersect1(scene, &context, &ray);

			if (ray.hit.geomID == MY_INVALID_GEOM_ID)
			{
				colors.push_back(Vec(0,0,0));
			}
			else {
				colors.push_back(Vec(255, 0, 0));
			}

			orgx += (1. - (-1.)) / (double)width;
			orgy += (1. - (-1.)) / (double)height;
		}
	}
	image.out(colors);

	/*  Release process */
	rtcReleaseScene(scene);
	rtcReleaseDevice(device);

	return 0;
}