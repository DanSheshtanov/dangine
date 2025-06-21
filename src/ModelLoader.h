#pragma once
#include <vector>
#include <DirectXMath.h>
#include <string>
#include <fstream>
#include <sstream>

#include "Debug.h"

class ModelLoader
{
public:
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<DirectX::XMFLOAT3> temp_vertices;
	std::vector<DirectX::XMFLOAT2> temp_texture_coords;
	std::vector<DirectX::XMFLOAT3> temp_normals;


	DirectX::XMFLOAT3 ParseFloat3(std::string verts)
	{
		DirectX::XMFLOAT3 out;
		std::istringstream ss{ verts };
		ss >> out.x;
		ss >> out.y;
		ss >> out.z;
		return out;
	}

	DirectX::XMFLOAT2 ParseFloat2(std::string verts)
	{
		DirectX::XMFLOAT2 out;
		std::istringstream ss{ verts };
		ss >> out.x;
		ss >> out.y;
		return out;
	}

	std::vector<std::string> split(std::string s, std::string delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}

	void LoadModel(std::string path)
	{
		using namespace std;
		using namespace DirectX;

		ifstream file{ path, ifstream::in };

		string line;
		while (getline(file, line))
		{
			istringstream ssLine{ line };
			string word;
			ssLine >> word;
			if (word == "v")
			{
				string coords;
				getline(ssLine, coords);
				XMFLOAT3 out = ParseFloat3(coords);
				temp_vertices.push_back(out);
			}
			else if (word == "vt")
			{
				string coords;
				getline(ssLine, coords);
				XMFLOAT2 out = ParseFloat2(coords);
				temp_texture_coords.push_back(out);
			}
			else if (word == "vn")
			{
				string coords;
				getline(ssLine, coords);
				XMFLOAT3 out = ParseFloat3(coords);
				temp_normals.push_back(out);
			}
			else if (word == "f")
			{
				string face;
				getline(ssLine, face);
				string p1, p2, p3;
				istringstream ssFace{ face };
				ssFace >> p1;
				ssFace >> p2;
				ssFace >> p3;
				LOG(face);
				LOG("\t" + p1 + ", " + p2 + ", " + p3);

				auto i1 = split(p1, "/")[0];
				auto i2 = split(p2, "/")[0];
				auto i3 = split(p3, "/")[0];
				vertexIndices.push_back(stoi(i1)-1);
				vertexIndices.push_back(stoi(i2)-1);
				vertexIndices.push_back(stoi(i3)-1);
			}
		}

		file.close();

		return;

		LOG("Vertex Coords");
		for (auto v : temp_vertices)
		{
			LOG("+\t" + to_string(v.x) + ", " + to_string(v.y) + ", " + to_string(v.z));
		}
		LOG("Texture Coords");
		for (auto v : temp_texture_coords)
		{
			LOG("+\t" + to_string(v.x) + ", " + to_string(v.y));
		}
		LOG("Vertex Normals");
		for (auto v : temp_normals)
		{
			LOG("+\t" + to_string(v.x) + ", " + to_string(v.y) + ", " + to_string(v.z));
		}
	}
};