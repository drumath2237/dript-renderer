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
	string path; // �t�@�C���p�X
	ifstream ifs; // �t�@�C���X�g���[��
	vector<Vec> vertices; // ���_�x�N�g��
	vector<Triangle> polys; // �O�p�ʃ|���S��
	vector<Vec> normals; // �@���x�N�g��
	
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
	// ���K�\��s
	regex vertex_exp("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex normal_exp("vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex face_exp("f (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*) (\\d*/\\d*/\\d*)");

	string text; // �t�@�C��������͂�����s���̕�����
	while (getline(ifs, text)) {

		smatch m; // ���K�\���}�b�`���[�B

		// ���_������̎擾�����_�̓o�^
		regex_search(text, m, vertex_exp);
		if (m.str() != "") {
			vertices.push_back(Vec(
				stoi(m[1].str()),
				stoi(m[2].str()),
				stoi(m[3].str())
			));
		}

		// �@���x�N�g���̎擾���o�^
		regex_search(text, m, normal_exp);
		if (m.str() != "") {
			normals.push_back(Vec(
				stoi(m[1].str()),
				stoi(m[2].str()),
				stoi(m[3].str())
			));
		}

	}

	ifs.close(); // �|���S���̎擾�̂��߂ɁA��������t�@�C�������

	ifs = ifstream(path);

	// �ʏ��̎擾
	while (getline(ifs, text))
	{
		// ���K�\���}�b�`���[�B�����makePolygonFromFace�ɓn�����Ƃ�
		// �}�b�`�������Ƃ��ۏ؂����Ɠ�����
		// �}�b�`���������񑀍삪�y�ɂȂ�
		smatch m;
		regex_search(text, m, face_exp);
		if (!m.empty()) {
			polys.push_back(makePolygonFromFace(m));
		}

	}

}

Triangle ObjFile::makePolygonFromFace(smatch m)
{
	regex re("(\\d*)/(\\d*)/(\\d*)"); // ���_�E�e�N�X�`�����W�E�@���x�N�g���̃C���f�b�N�X���擾���鐳�K�\��
	smatch matches[3]; // ���K�\������̃f�[�^���擾���邽�߂̃}�b�`���[

	// �v�f�� /(\d*)/(\d*)/(\d*)/ �̐��K�\���ɐ�΃}�b�`����B
	// �Ȃ�face�Ƃ������O�ɂ����̂��킩��񂯂�
	string faces[3] = {
		m[1].str(),
		m[2].str(),
		m[3].str()
	};

	int index[3]; // �擾�������_�̃C���f�b�N�X���i�[����z��
	for (auto i = 0; i < 3; i++) {
		regex_search(faces[i], matches[i], re);

		// re�̈�ԍŏ��̃}�b�`��������������Q�Ƃ���ƒ��_�̃C���f�b�N�X�����Ƃ��
		// ����𕶎���to���l���Ă�
		index[i] = stoi(matches[i][1].str());
	}

	// .obj�̃C���f�b�N�X��1����Ȃ̂�-1����0����n�߂�悤�ɂ���
	Triangle result = Triangle(
		vertices[index[0] - 1],
		vertices[index[1] - 1],
		vertices[index[2] - 1]
	);

	// �@�����̎擾
	// matches�͂ǂ�ł�����(����Ȃ�������)
	result.normal = normals[stoi(matches[0][3]) - 1];

	return result;
}
