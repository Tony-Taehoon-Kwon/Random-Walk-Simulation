#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

namespace SimulationSection
{
	class OBJLoader
	{
	public:
		OBJLoader() : isFirstScan(true) {}
		bool loadOBJ(const char* path);

	public:
		std::vector<glm::vec3> m_vertices;
		std::vector<unsigned int> m_vertexIndices;

		/* variable for calculating middle point of the object */
		glm::vec3 min, max;
		bool isFirstScan;
	};
}