#pragma once


class EasyPlyLoader
{
public:
	static void loadPlyParticles(const std::string absFileName, std::vector<Vector3r>& particlePos)
	{
		happly::PLYData plyIn(absFileName);
		std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
		printf("Reading ply file: %s\n", absFileName.c_str());
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