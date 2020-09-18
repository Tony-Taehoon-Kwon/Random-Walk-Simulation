#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <map>

namespace SimulationSection
{
	class Camera;
	class Shader;

	class Model
	{
	private:
		unsigned m_vao, m_vbo, m_ibo, m_vnvbo_attrib;
		std::vector<glm::vec3> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<glm::vec3> m_faceNormal, m_faceNormalBeginPoint;
		std::vector<glm::vec3> m_vertexNormal;
		std::vector<glm::vec3> m_faceNormalBuffer, m_vertexNormalBuffer;
		std::multimap<int, glm::vec3> m_vertexIntermediateNormalBuffer;
		typedef std::multimap<int, glm::vec3>::iterator ITOR;

	public:

		Model() {}
		Model(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
		~Model();

		void CreateModel(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
		void Render(Camera* camera, Shader* shader, float aspect, unsigned int mode, int dimension, float mainAxisDomain);
		std::vector<glm::vec3> GetFaceNormals(void);
		std::vector<glm::vec3> GetVertexNormals(void);

		glm::vec3 position, scale, color, rotation, I_emissive;
		glm::vec3 min, max;
		float k_a, k_d;
	};
}