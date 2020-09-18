#include "ObjLoader.h"

using namespace SimulationSection;

bool OBJLoader::loadOBJ(const char* path)
{
	printf("Loading OBJ file %s...", path);

	/* open the file */
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !");
		getchar();
		return false;
	}

	/* read file */
	while (1)
	{
		char lineHeader[128];

		/* read the first word of the line */
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			/* calculate the middle point */
			glm::vec3 middlePoint((max.x + min.x) / 2.f, (max.y + min.y) / 2.f, (max.z + min.z) / 2.f);

			/* move the object to the origin by subtracting the middle point */
			for (unsigned int i = 0; i < m_vertices.size(); ++i)
				m_vertices[i] -= middlePoint;

			min -= middlePoint;
			max -= middlePoint;

			break; // EOF = End Of File. Quit the loop.
		}

		/* vertex section */
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (isFirstScan)
			{
				max = vertex;
				min = vertex;
				isFirstScan = false;
			}
			else
			{
				if (max.x > vertex.x)		max.x = vertex.x;
				if (max.y > vertex.y)		max.y = vertex.y;
				if (max.z > vertex.z)		max.z = vertex.z;
				if (min.x < vertex.x)		min.x = vertex.x;
				if (min.y < vertex.y)		min.y = vertex.y;
				if (min.z < vertex.z)		min.z = vertex.z;
			}

			/* store the vertex buffer */
			m_vertices.push_back(vertex);
		}
		/* face section */
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3];
			int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			if (matches != 3) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}

			/* store the index buffer (-1 because c++ index is start with 0 and obj index is start with 1) */
			m_vertexIndices.push_back(vertexIndex[0] - 1);
			m_vertexIndices.push_back(vertexIndex[1] - 1);
			m_vertexIndices.push_back(vertexIndex[2] - 1);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	fclose(file);

	printf("Completed\n");

	return true;
}