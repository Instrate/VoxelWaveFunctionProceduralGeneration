#pragma once
#define GLEW_STATIC

#include <vector>
#include <string>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/json.hpp>

#include "Manager.h"
#include "Shader.h"

#include "EngineSettings.h"

class GameWindow {
private:

	Manager threads;

	std::vector<int> size;
	
	Shader* shader;

	EngineSettings* settings;

public:

	std::string name;

	GLFWwindow* window;

	GameWindow() {
		settings = new EngineSettings();
		
		SettingsReset();
	}

	bool SettingsReset() {
		this->size = settings->PathWindowSizeGetValue();
		this->name = settings->PathWindowNameGetValue();

		if (!Init()) {
			return false;
		}

		

		shader = new Shader(
			settings->PathShaderGetValue("VERT"),
			settings->PathShaderGetValue("FRAG")
		);

		return true;
	}

	bool Init(bool isFullScreen = false) {

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(
			size[0],
			size[1],
			name.c_str(),
			isFullScreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr
		);

		if (!window)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();

		return true;
	}


	void Render() {
		/* Render here */

		glClearColor(0.5, 0.5, 0.8, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glfwSwapBuffers(window);


		glfwPollEvents();
	}



	void Run() {
		

		while (!ShouldTerminate()) {
			
			
			Render();
		}
	}

	bool ShouldTerminate() {
		return glfwWindowShouldClose(window);
	}




};