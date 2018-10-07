#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "polygon.h"
#include "vec.h"

using namespace std;

struct ObjFile
{
	//members
	string path;
	ifstream ifs;
	vector<Vec> vertices;
	vector<Polygon3> polys;
	vector<Vec> normals;
	
	// constructor
	ObjFile(string p);

	// methods
private:
	void importPolygons();

};

ObjFile::ObjFile(string p) :path(p), ifs(ifstream(path)) {
	if (ifs.fail()) {
		cout << "!!! File import failed !!!" << endl;
		return;
	}
	importPolygons();
}

void ObjFile::importPolygons()
{
	regex vertex_exp("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex normal_exp("vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex face_exp("f (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*)");
	regex face_analysis_exp("(\\d*)/(\\d*)/(\\d*)");

	string text;
	while (getline(ifs, text)) {
		smatch m;
		regex_search(text, m, vertex_exp);
		if (m.str() != "") {
			vertices.push_back(Vec(
				stoi(m[1].str()),
				stoi(m[2].str()),
				stoi(m[3].str())
			));
		}

		regex_search(text, m, normal_exp);
		if (m.str() != "") {
			normals.push_back(Vec(
				stoi(m[1].str()),
				stoi(m[2].str()),
				stoi(m[3].str())
			));
		}
	}

	ifs.close();
	ifs = ifstream(path);
	while (getline(ifs, text))
	{
		smatch m;
		regex_search(text, m, face_exp); // m->f (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*)

		if (!m.empty()) {
			int index[3]; // polygon3‚Ì3‚Â‚Ìƒ|ƒŠƒSƒ“‚ğQÆ‚·‚é‚½‚ß‚Ì“Y‚¦š

			for (int i = 0; i < 3; i++) {
				smatch m_tmp;
				string str_tmp;
				str_tmp = m[i+1].str();
				regex_search(str_tmp, m_tmp, face_analysis_exp);
				index[i] = stoi(m_tmp[1].str());
			}

			polys.push_back(Polygon3(
				vertices[index[0]],
				vertices[index[1]],
				vertices[index[2]]
			));

		}

	}
}
