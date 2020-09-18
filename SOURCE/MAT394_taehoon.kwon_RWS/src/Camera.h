#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace SimulationSection
{
	const float YAW = -135.0f;
	const float PITCH = -30.0f;
	const float SPEED = 10.0f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;
	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
}

namespace SimulationSection
{
	class Shader;
	public class Camera
	{
	public:
		glm::vec3 position, front, up, right, worldUp;
		float yaw, pitch;

		float movementSpeed;
		float mouseSensitivity;
		float zoom;

	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
			   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
			   glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
			   float yaw = YAW, float pitch = PITCH);
		glm::mat4 GetViewMatrix();
		void Update(Shader* _shader);
		void ProcessKeyboard(Camera_Movement direction, float deltaTime, int dimension);

		void ProcessMouseMovement(float xoffset, float yoffset, int dimension, GLboolean constrainPitch = false);
		void ProcessMouseScroll(float yoffset);
		void updateCameraVectors();
	};
}