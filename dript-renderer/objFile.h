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
	Polygon3 makePolygonFromFace(smatch);

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
		regex_search(text, m, face_exp);
		if (!m.empty()) {
			polys.push_back(makePolygonFromFace(m));
		}

	}
}

Polygon3 ObjFile::makePolygonFromFace(smatch m)
{
	regex re("(\\d*)/(\\d*)/(\\d*)");
	smatch matches[3];

	string faces[3] = {
		m[1].str(),
		m[2].str(),
		m[3].str()
	};

	int index[3];
	for (auto i = 0; i < 3; i++) {
		regex_search(faces[i], matches[i], re);
		index[i] = stoi(matches[i][1].str());
	}

	Polygon3 result = Polygon3(
		vertices[index[0] - 1],
		vertices[index[1] - 1],
		vertices[index[2] - 1]
	);

	return result;
}
