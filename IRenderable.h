#pragma once

#include "Shader.hpp"

class IRenderable {
public:
	virtual void Render(const Shader& shader, const GLenum& mode) = NULL;
};