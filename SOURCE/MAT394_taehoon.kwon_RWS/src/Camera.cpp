#include "Camera.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace SimulationSection;

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front,
				float yaw, float pitch)
	: position(position), up(up), worldUp(WORLD_UP), front(front),
	  yaw(yaw), pitch(pitch), zoom(ZOOM),
	  movementSpeed(SPEED), mouseSensitivity(SENSITIVITY)
{
	right = glm::normalize(glm::cross(front, up));
	glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update(Shader* _shader)
{
	_shader->SetUniform3fv("viewPos", position);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime, int dimension)
{
	float velocity = movementSpeed * deltaTime;

	if (dimension == 3)
	{
		if (direction == FORWARD)
			position += front * velocity;

		if (direction == BACKWARD)
			position -= front * velocity;

		if (direction == LEFT)
			position -= right * velocity;

		if (direction == RIGHT)
			position += right * velocity;
	}
	else
	{
		if (direction == FORWARD)
			position += up * velocity;

		if (direction == BACKWARD)
			position -= up * velocity;

		if (direction == LEFT)
			position += right * velocity;

		if (direction == RIGHT)
			position -= right * velocity;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, int dimension, GLboolean constrainpitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	if (dimension == 3)
	{
		yaw += xoffset;
		pitch += yoffset;

		if (constrainpitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateCameraVectors();
	}
	else
	{
		position.x += (xoffset / 2.f);
		position.y -= (yoffset / 2.f);
	}
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 _front;
	_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front.y = sin(glm::radians(pitch));
	_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(_front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}