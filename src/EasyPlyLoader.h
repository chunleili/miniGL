#pragma once

#include "EasyFilePath.h"

class EasyPlyLoader
{
public:
	static void loadPlyParticles(const std::string fileName, std::vector<Vector3r>& particlePos)
	{
		// Construct a data object by reading from file
		std::filesystem::path filePath = EasyFilePath::modelDir / fileName;
		auto fullPathString = filePath.string();

		happly::PLYData plyIn(fullPathString);
		std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
		printf("Reading ply file: %s\n", fullPathString.c_str());
		printf("Number of vertices: %d\n", int(vPos.size()));
		// copy data to particlePos
		particlePos.resize(vPos.size());
		for (int i = 0; i < vPos.size(); i++)
		{
			particlePos[i] = Vector3r(vPos[i][0], vPos[i][1], vPos[i][2]);
		}
		printf("End Reading ply file\n");
	}
};