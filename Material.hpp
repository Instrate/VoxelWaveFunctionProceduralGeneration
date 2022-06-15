#pragma once

#include <glm/glm.hpp>


class Material {
public:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	float opacity;

	
	explicit Material(
		const glm::vec3& ambient = glm::vec3(1.0f),
		const glm::vec3& diffuse = glm::vec3(1.0f),
		const glm::vec3& specular = glm::vec3(1.0f),
		const float& shininess = 32,
		const float& opacity = 1
	) {
		Switch(
			ambient,
			diffuse,
			specular,
			shininess,
			opacity);
	}

	void Switch(
		const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular,
		const float& shininess,
		const float& opacity
	) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
		this->opacity = opacity;
	}
};
