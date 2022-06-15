#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

#include "Shader.hpp"

#include <SOIL/SOIL.h>


class Texture {
public:

	static GLuint LoadFromFile (
		const std::string &path,
		bool hasBorder = false,
		glm::vec4 const borderColor = glm::vec4(0),
		GLuint wrapmode = GL_REPEAT,
		GLuint LODbiasMIN = GL_LINEAR_MIPMAP_LINEAR,
		GLuint LODbiasMAG = GL_LINEAR
	) {
		GLuint handle;
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);

		int width;
		int height;
		unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, LODbiasMIN);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, LODbiasMAG);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapmode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapmode);

		if (hasBorder && wrapmode == GL_CLAMP_TO_BORDER) {
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &borderColor[0]);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		return handle;
	}

	static void Use(const Shader& shader, std::vector<GLuint> const &textureHandlers) {
		if (textureHandlers.empty()) {
			return;
		}
		int amount = textureHandlers.size();
		shader.Use();
		GLint uniformLoc = glGetUniformLocation(shader.Handle, "textures[0]");
		glUniform1uiv(uniformLoc, amount, &textureHandlers[0]);
		for (int unit = 0; unit < amount; unit++) {
			glActiveTexture(GL_TEXTURE0 + unit);
		}
		glBindTextures(textureHandlers[0], amount, &textureHandlers[0]);
	}
};