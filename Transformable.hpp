
#include <array>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Material.hpp"
#include "Shader.hpp"
#include "Moveable.hpp"
#include "Texture.hpp"


class Transformable : protected Moveable {
protected:

	std::vector<GLuint> textureHandlers;

	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	Transformable* parent = nullptr;

	Material material;

	virtual void applyTextures(const Shader& shader) {
		Texture::Use(shader, textureHandlers);
	}

	virtual void applyMaterial(const Shader& shader) {
		const Material mat = (parent != nullptr) ? parent->material : material;

		shader.SetVector3("material.ambient", mat.ambient);
		shader.SetVector3("material.diffuse", mat.diffuse);
		//shader.SetVector3("material.specular", mat.specular);
		//shader.SetFloat("material.shininess", mat.shininess);
		shader.SetFloat("material.opacity", mat.opacity);
	}

	// TODO: check usability
	/*void prepareRendering(const Shader& shader) override{
		GLint uniformLoc = glGetUniformLocation(shader.Handle, "transform");
		glUniformMatrix4fv(uniformLoc, 1, false, (GLfloat*)&transform[0]);
	}*/

	virtual void LoadTextureSet(const std::vector<std::string>& textureSet) {
		if (!textureSet.empty()) {
			for (auto texture : textureSet) {
				textureHandlers.push_back(Texture::LoadFromFile(texture));
			}
		}
	}

public:

	virtual void Rotate(const glm::vec3& angles) {
		const glm::mat4 rotateX = glm::rotate(glm::mat4(1), angles.x, glm::vec3(1, 0, 0));
		const glm::mat4 rotateY = glm::rotate(glm::mat4(1), angles.y, glm::vec3(0, 1, 0));
		const glm::mat4 rotateZ = glm::rotate(glm::mat4(1), angles.z, glm::vec3(0, 0, 1));
		rotation *= rotateX * rotateY * rotateZ;
		TransformCombine();
	}

	virtual void Scale(const glm::vec3& scalar) {
		scale *= glm::scale(glm::mat4(1), scalar);
		TransformCombine();
	}

	void TransformCombine() override {
		transform = scale * rotation * originShift;
	}
	
	void TransformClean() override {
		transform = glm::mat4(1);
		originShift = glm::mat4(1);
		rotation = glm::mat4(1);
		scale = glm::mat4(1);
	}

	
	void Render(const Shader& shader, const GLenum& mode) override{
		if (isEnabled) {
			applyTextures(shader);
			prepareRendering(shader);
			applyMaterial(shader);
			renderObject(shader, mode);
		}
	}
};