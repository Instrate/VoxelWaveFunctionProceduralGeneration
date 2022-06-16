#pragma once

#include <vector>
#include <array>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Transformable.hpp"
#include "Indexable.hpp"
#include "Shader.hpp"

#include "DefaultData.hpp"

using namespace data::square;

class Square : protected Indexable, protected Transformable {
private:

	std::array<GLfloat, offset * 4> vertices;

	void BindObject() override {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat), nullptr);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat), vertices.data() + (3 * sizeof(GLfloat)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat), vertices.data() + (5 * sizeof(GLfloat)));
	}

	std::array<GLfloat, 12> BuildCoords(const std::array<glm::vec3, 3>& p) {
		std::array<GLfloat, 12> coords;
		const int offset = 3;

		for (int i = 0; i < 3; i++) {
			coords[i] = 0;
		}
		for (int i = 1; i < 4; i++) {
			for (int j = 0; j < offset; j++) {
				coords[i * offset + j] = p[i - 1][j];
			}
		}
		return coords;
	}

	void PlaceObject(const std::array<glm::vec3, 4>& points) {
		std::array<glm::vec3, 3> vecs;
		for (int i = 1; i < 4; i++) {
			vecs[i - 1] = points[i] - points[0];
		}
		Move(points[0]);
		static const std::array<GLfloat, 12> coords = BuildCoords(vecs);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				vertices[i * offset + j] = coords[i * 3 + j];
			}
			for (int j = 0; j < 2; j++) {
				vertices[i * offset + 3 + j] = texture[i * 2 + j];
			}
			for (int j = 0; j < 3; j++) {
				vertices[i * offset + 5 + j] = normal[i * 3 + j];
			}
		}
	}

	void renderObject(const Shader& shader, const GLenum& mode = GL_TRIANGLES) const override {
		glBindVertexArray(VAO);
		glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, indices.data());
		glBindVertexArray(0);
	}

public:

	Square(
		const std::array<glm::vec3, 4>& points,
		const std::vector<std::string>& textureSet,
		const glm::vec4& color = glm::vec4(1),
		Transformable* parent = nullptr
	) {
		PlaceObject(points);
		BindObject();
		LoadTextureSet(textureSet);
		this->color = color;
		this->parent = parent;
		isEnabled = true;
	}

	~Square() override {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &VAO);
		glDeleteBuffers(1, &EBO);
	}

};