#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "vec.h"

using namespace std;

struct PPM
{
	int width = 600;
	int height = 400;
	int max_color = 255;
	string file_path = "./result.ppm";

	PPM() {};
	PPM(int w, int h):width(w),height(h){}

	int size() { return width * height; }
	bool out(vector<Vec>);
	bool ppm_out(PPM, vector<Vec>);
};

bool PPM::out(vector<Vec> colors)
{
	if (size() != colors.size()) return false;
	ppm_out(*this, colors);
	return true;
}

bool PPM::ppm_out(PPM ppm, vector<Vec> colors)
{
	if (ppm.size() != colors.size()) return false;

	ofstream ofs(ppm.file_path);
	ofs << "P3\n" << ppm.width << " " << ppm.height << "\n" << ppm.max_color << endl;

	for (auto v : colors) {
		ofs << v.x << " "
			<< v.y << " "
			<< v.z << endl;
	}

	return true;
}