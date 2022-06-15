#pragma once

#include <iostream>

#include <fstream>

#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "FileLoader.h"

class Shader {
private:
	
	GLint Handle;
	
	std::map<std::string, int> _uniformLocations;

	// TODO: make correct error proccessing
	static void CompileShader(GLint shader) {
		glCompileShader(shader);
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			const GLint bufsize = 256;
			GLchar infoLog[bufsize];
			GLint len;
			glGetShaderInfoLog(shader, bufsize, &len, infoLog);
			exit(EXIT_FAILURE);
			//throw "Error occurred whilst compiling Shader(" + std::to_string(shader) + ").\n\n" + infoLog;
		}
	}

	// TODO: make correct error proccessing
	static void LinkProgram(GLint program) {
		glLinkProgram(program);
		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			const GLint bufsize = 256;
			GLchar infoLog[bufsize];
			GLint len;
			glGetProgramInfoLog(program, bufsize, &len, infoLog);
			exit(EXIT_FAILURE);
			//throw "Error occurred whilst linking Program(" + std::to_string(program) + ").\n\n" + infoLog;
		}
	}

public:

	Shader(const std::string& vertPath, const std::string& fragPath) {

		std::string source = ReadAllText(vertPath);
		const char* vertexSource = source.c_str();
		GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, 0);
		CompileShader(vertexShader);

		source = ReadAllText(fragPath);
		const char* fragmentSource = source.c_str();
		GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, 0);
		CompileShader(fragmentShader);

		Handle = glCreateProgram();
		glAttachShader(Handle, vertexShader);
		glAttachShader(Handle, fragmentShader);
		LinkProgram(Handle);

		glDetachShader(Handle, vertexShader);
		glDetachShader(Handle, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		std::vector<std::string> uniforms;
		const GLsizei bufsize = 64;
		GLchar name[bufsize];
		GLint size;
		GLenum type;
		GLsizei len;
		GLint numActiveUniforms = 0;

		glGetProgramInterfaceiv(Handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms);

		for (int uniform = 0; uniform < numActiveUniforms; uniform++) {
			glGetActiveUniform(Handle, (GLint)uniform, bufsize, &len, &size, &type, name);
			_uniformLocations.insert(std::pair(name, uniform));
		}
	}

	void SetInt(const std::string& name, int data) const {
		glUseProgram(Handle);
		glUniform1i(glGetUniformLocation(Handle, name.c_str()), data);
	}

	void SetFloat(const std::string& name, float data) const {
		glUseProgram(Handle);
		glUniform1f(glGetUniformLocation(Handle, name.c_str()), data);
	}

	void SetVector3(const std::string& name, glm::vec3 data) const {
		glUseProgram(Handle);
		glUniform3f(glGetUniformLocation(Handle, name.c_str()), data.x, data.y, data.z);
	}

	void SetMatrix4(const std::string& name, glm::mat4 data) const {
		glUseProgram(Handle);
		glUniformMatrix4fv(glGetUniformLocation(Handle, name.c_str()), 1, false, (GLfloat*)&data[0]);
	}

};