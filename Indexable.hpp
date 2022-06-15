#pragma once

#include <GL/glew.h>

class Indexable {
protected:

	GLfloat* vertices;

	GLint offset;

	GLint VBO;
	GLint VAO;
	GLint EBO;

};