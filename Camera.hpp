#pragma once

#include <boost/math/constants/constants.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace constants = boost::math::constants;

class Camera {
private:

	glm::vec3 front = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::vec3(1, 0, 0);

	float pitch = 0;

	float yaw = -constants::pi<float>() / 2.f;

	float fov = constants::pi<float>() / 2.f;

	void UpdateVectors() {
		front.x = cos(pitch) * cos(yaw);
		front.y = cos(pitch) * sin(yaw);
		front.z = sin(pitch);

		front = glm::normalize(front);

		right = glm::normalize(glm::cross(front, glm::vec3(0, 0, 1)));
		up = glm::normalize(glm::cross(right, front));
	}

public:
	
	glm::vec3 position;

	explicit Camera(const glm::vec3& pos) {
		position = pos;
	}

	float PitchGet() const {
		return glm::degrees(pitch);
	}

	void PitchSet(const float& value) {
		const float angle = glm::clamp(value, -89.f, 89.f);
		pitch = glm::radians(angle);
		UpdateVectors();
	}

	float YawGet() const {
		return glm::degrees(yaw);
	}

	void YawSet(const float& value) {
		yaw = glm::radians(fmod(value, 360.f));
		UpdateVectors();
	}

	float FovGet() const {
		return glm::degrees(fov);
	}

	void FovSet(const float& value) {
		float angle = glm::clamp(value, 45.f, 90.f);
		fov = glm::radians(angle);
	}

	glm::mat4 GetViewMatrix() const {
		return glm::lookAt(position, position + front, up);
	}

	glm::mat4 GetProjectionMatrix(const float& width, const float& height) const {
		return glm::perspectiveFov(fov, width, height, 0.01f, 1000.f);
	}
};