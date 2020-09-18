#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Camera.h"
#include "Shader.h"

#include <GLFW/glfw3.h>

using namespace SimulationSection;

Model::Model(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
	: position(glm::vec3()), scale(glm::vec3(1, 1, 1)), rotation(glm::vec3())
{
	CreateModel(vertices, indices);
}

void Model::CreateModel(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
	m_vertices = vertices;
	m_indices = indices;

	/* Generate vertex array object */
	glGenVertexArrays(1, &m_vao);
	/* Generate vertex buffer object */
	glGenBuffers(1, &m_vbo);
	/* Generate index buffer object */
	glGenBuffers(1, &m_ibo);
	/* Generate vertex normal buffer object */
	glGenBuffers(1, &m_vnvbo_attrib);

	/* Calculate face normal */
	GetFaceNormals();
	/* Calculate vertex normal */
	GetVertexNormals();
	
	/* Describe the Vertex attribute */
	const GLsizei vertex_size_stride = 0 * sizeof(float);
	constexpr GLint three_components_in_vertex_position = 3;
	constexpr GLint three_components_in_vertex_normal = 3;
	constexpr GLenum float_element_type = GL_FLOAT;
	constexpr GLboolean not_fixedpoint = GL_FALSE;
	const void* position_offset_in_vertex = reinterpret_cast<void*>(0);
	const void* normal_offset_in_vertex = reinterpret_cast<void*>(0);

	/* Bind vertex array object */
	glBindVertexArray(m_vao);
	/* Bind vertex buffer object for the purpose of Vertex Attributes */
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	/* Copy the vertices from ram to vram and hint to opengl that it will be used for static draws */
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	/* Enable the 1st attribute */
	glEnableVertexAttribArray(0);
	/* Describe the 1st attribute - this is to be used for positions */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	/* Bind vertex normal vertex buffer object for the purpose of Vertex Attributes */
	glBindBuffer(GL_ARRAY_BUFFER, m_vnvbo_attrib);
	/* Copy the vertices from ram to vram and hint to opengl that it will be used for static draws */
	glBufferData(GL_ARRAY_BUFFER, (unsigned int)m_vertexNormal.size() * sizeof(glm::vec3),
		&m_vertexNormal[0], GL_STATIC_DRAW);

	/* Enable the 2nd attribute */
	glEnableVertexAttribArray(1);
	/* Describe the 2nd attribute - this is to be used for normals */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	/* Bind the index buffer object for the purpose of Vertex buffer indices */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	/* Copy the indices from ram to vram and hint to opengl that it will be used for static draws */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	/* Unbind vertex array */
	glBindVertexArray(0);

	k_a = 0.046f;
	k_d = 0.364f;
}

Model::~Model()
{
	/* Delete the vertex array */
	glDeleteVertexArrays(1, &m_vao);
	/* Delete the vertex buffer */
	glDeleteBuffers(1, &m_vbo);
	/* Delete the index buffer */
	glDeleteBuffers(1, &m_ibo);
	/* Delete the vertex normal vertex buffer */
	glDeleteBuffers(1, &m_vnvbo_attrib);
}

std::vector<glm::vec3> Model::GetFaceNormals()
{
	/* if face normal is already calculated, then skip the calculation */
	if (m_faceNormalBuffer.size() != 0)
		return m_faceNormalBuffer;

	/* for all indices */
	for (size_t i = 0; i < m_indices.size(); i += 3)
	{
		/* calculate the face normal */
		glm::vec3 v0 = m_vertices[m_indices[i]] - m_vertices[m_indices[i + 1]];
		glm::vec3 v1 = m_vertices[m_indices[i + 2]] - m_vertices[m_indices[i + 1]];
		m_faceNormal.push_back(glm::normalize(glm::cross(v1, v0)) * glm::vec3(0.01f)); //*glm::vec3(0.1f)

		/* calculate the center of the triangle */
		m_faceNormalBeginPoint.push_back(glm::vec3((m_vertices[m_indices[i]].x + m_vertices[m_indices[i + 1]].x + m_vertices[m_indices[i + 2]].x) / 3,
			(m_vertices[m_indices[i]].y + m_vertices[m_indices[i + 1]].y + m_vertices[m_indices[i + 2]].y) / 3,
			(m_vertices[m_indices[i]].z + m_vertices[m_indices[i + 1]].z + m_vertices[m_indices[i + 2]].z) / 3));

		/* for each vertices on the triangle, add the triangle face normal */
		m_vertexIntermediateNormalBuffer.insert(std::make_pair(m_indices[i], m_faceNormal[i / 3]));
		m_vertexIntermediateNormalBuffer.insert(std::make_pair(m_indices[i + 1], m_faceNormal[i / 3]));
		m_vertexIntermediateNormalBuffer.insert(std::make_pair(m_indices[i + 2], m_faceNormal[i / 3]));
	}

	/* for all face normal */
	for (size_t i = 0; i < m_faceNormal.size(); ++i)
	{
		/* store the begin point and end point of the line */
		m_faceNormalBuffer.push_back(m_faceNormalBeginPoint[i]);
		m_faceNormalBuffer.push_back(m_faceNormalBeginPoint[i] + m_faceNormal[i]);
	}
	return m_faceNormalBuffer;
}

std::vector<glm::vec3> Model::GetVertexNormals(void)
{
	/* if vertex normal is already calculated, then skip the calculation */
	if (m_vertexNormalBuffer.size() != 0)
		return m_vertexNormalBuffer;

	/* for all vertices */
	for (size_t i = 0; i < m_vertices.size(); ++i)
	{
		std::pair<ITOR, ITOR> result = m_vertexIntermediateNormalBuffer.equal_range(i);
		std::vector<glm::vec3> temp;

		/* Duplicate check */
		/* for all values with key i(loop counter)
		   (= for all adjacent face normals of a vertex )*/
		for (ITOR itor = result.first; itor != result.second; ++itor)
		{
			bool isOccupied = false;

			for (ITOR itor2 = itor; itor2 != result.second; ++itor2)
			{
				if (itor == itor2)
					continue;

				if (itor->second == itor2->second)
				{
					isOccupied = true;
					break;
				}
			}

			if (isOccupied == false)
				temp.push_back(itor->second);
		}

		glm::vec3 averageVector(0);

		for (size_t i = 0; i < temp.size(); ++i)
			averageVector += temp[i];
		averageVector = glm::normalize(averageVector);

		m_vertexNormal.push_back(averageVector);

		/* store the begin point and end point of the line */
		m_vertexNormalBuffer.push_back(m_vertices[i]);
		m_vertexNormalBuffer.push_back(m_vertices[i] + m_vertexNormal[i]);
	}
	return m_vertexNormalBuffer;
}

void Model::Render(Camera* camera, Shader* shader,
					float aspect, unsigned int mode,
					int dimension, float mainAxisDomain)
{
	/* Rotating axis */
	const static glm::vec3 up(0, 1, 0);
	const static glm::vec3 right(1, 0, 0);
	const static glm::vec3 backward(0, 0, 1);

	/* identity matrix */
	glm::mat4 identity_translate(1.0);
	glm::mat4 identity_scale(1.0);
	glm::mat4 identity_rotation(1.0);

	/* Declare matrices for model, projection, and viewport */
	glm::mat4 model = glm::translate(identity_translate, position)
		* glm::scale(identity_scale, scale)
		* glm::rotate(identity_rotation, rotation.x, right)
		* glm::rotate(identity_rotation, rotation.y, up)
		* glm::rotate(identity_rotation, rotation.z, backward);
	glm::mat4 view, projection;

	if (dimension == 3)
	{
		projection = glm::perspective(glm::radians(camera->zoom), aspect, 0.1f, 100.0f);
		view = camera->GetViewMatrix();
	}
	else
	{
		view = glm::mat4(1.0);
		projection = glm::ortho((-mainAxisDomain + camera->position.x) *camera->zoom /30.f * aspect,	// left
								 (mainAxisDomain + camera->position.x) *camera->zoom /30.f * aspect,	// right
								 (mainAxisDomain + camera->position.y) *camera->zoom /30.f,				// bottom
								(-mainAxisDomain + camera->position.y) *camera->zoom /30.f,				// top
								-1.0f, 1.0f);
	}

	/* Set uniform location of each matrices, color */
	shader->SetUniformMatrix4fv("model", model);
	shader->SetUniformMatrix4fv("view", view);
	shader->SetUniformMatrix4fv("projection", projection);
	shader->SetUniform3fv("objectColor", color);
	shader->SetUniform1f("k_a", k_a);
	shader->SetUniform1f("k_d", k_d);

	/* bind the vertex array */
	glBindVertexArray(m_vao);

	/* draw the model */
	glDrawElements(mode, m_indices.size(), GL_UNSIGNED_INT, nullptr);

	/* Unbind vertex array */
	glBindVertexArray(0);
}