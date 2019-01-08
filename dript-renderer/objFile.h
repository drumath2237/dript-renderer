#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "triangle.h"
#include "vec.h"

using namespace std;

struct ObjFile
{
	//members
	string path; // ファイルパス
	ifstream ifs; // ファイルストリーム
	vector<Vec> vertices; // 頂点ベクトル
	vector<Triangle> polys; // 三角面ポリゴン
	vector<Vec> normals; // 法線ベクトル
	
	// constructor
	ObjFile(string p);

	// methods
private:
	void importPolygons();
	Triangle makePolygonFromFace(smatch);

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
	// 正規表現s
	regex vertex_exp("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex normal_exp("vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex face_exp("f (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*)");

	string text; // ファイルから入力される一行分の文字列
	while (getline(ifs, text)) {

		smatch m; // 正規表現マッチャー。

		// 頂点文字列の取得→頂点の登録
		regex_search(text, m, vertex_exp);
		if (m.str() != "") {
			vertices.push_back(Vec(
				stoi(m[1].str()),
				stoi(m[2].str()),
				stoi(m[3].str())
			));
		}

		// 法線ベクトルの取得→登録
		regex_search(text, m, normal_exp);
		if (m.str() != "") {
			normals.push_back(Vec(
				stoi(m[1].str()),
				stoi(m[2].str()),
				stoi(m[3].str())
			));
		}

	}

	ifs.close(); // ポリゴンの取得のために、いったんファイルを閉じる

	ifs = ifstream(path);

	// 面情報の取得
	while (getline(ifs, text))
	{
		// 正規表現マッチャー。これをmakePolygonFromFaceに渡すことで
		// マッチしたことが保証されると同時に
		// マッチした文字列操作が楽になる
		smatch m;
		regex_search(text, m, face_exp);
		if (!m.empty()) {
			polys.push_back(makePolygonFromFace(m));
		}

	}

}

Triangle ObjFile::makePolygonFromFace(smatch m)
{
	regex re("(\\d*)/(\\d*)/(\\d*)"); // 頂点・テクスチャ座標・法線ベクトルのインデックスを取得する正規表現
	smatch matches[3]; // 正規表現からのデータを取得するためのマッチャー

	// 要素は /(\d*)/(\d*)/(\d*)/ の正規表現に絶対マッチする。
	// なぜfaceという名前にしたのかわからんけど
	string faces[3] = {
		m[1].str(),
		m[2].str(),
		m[3].str()
	};

	int index[3]; // 取得した頂点のインデックスを格納する配列
	for (auto i = 0; i < 3; i++) {
		regex_search(faces[i], matches[i], re);

		// reの一番最初のマッチ部分だけを後方参照すると頂点のインデックスだけとれる
		// それを文字列to数値してる
		index[i] = stoi(matches[i][1].str());
	}

	// .objのインデックスは1からなので-1して0から始めるようにする
	Triangle result = Triangle(
		vertices[index[0] - 1],
		vertices[index[1] - 1],
		vertices[index[2] - 1]
	);

	// 法線情報の取得
	// matchesはどれでもいい(おんなじだから)
	result.normal = normals[stoi(matches[0][3]) - 1];

	return result;
}
