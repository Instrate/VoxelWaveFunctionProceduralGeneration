#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IRenderable.h"
#include "Shader.hpp"

class Moveable : public IRenderable {
protected:

	glm::vec3 color = glm::vec3(1);

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 originShift = glm::mat4(1.0f);


	virtual void BindObject() = NULL;
	
	virtual void renderObject(const Shader& shader, const GLenum& mode) const = NULL;

	virtual void prepareRendering(const Shader& shader) {
		GLint uniformLoc = glGetUniformLocation(shader.Handle, "transform");
		glUniformMatrix4fv(uniformLoc, 1, false, (GLfloat*)&transform[0]);
	}

public:
	bool isEnabled = false;

	glm::vec3 position = glm::vec3(0.0f);

	virtual void Move(const glm::vec3& shifts) {
		position += shifts;
		originShift += glm::translate(glm::mat4(1.0f), shifts);
		
		TransformCombine();
	}

	virtual void TransformCombine() {
		transform = originShift;
	}

	virtual void TransformClean() {
		transform = glm::mat4(1.0f);
		originShift = glm::mat4(1.0f);
	}

	void Render(const Shader& shader, const GLenum& mode) override {
		if (isEnabled) {
			prepareRendering(shader);
			renderObject(shader, mode);
		}
	}

	virtual ~Moveable() = default;
};