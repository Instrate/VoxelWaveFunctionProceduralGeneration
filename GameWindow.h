#pragma once
#include <vector>
#include <string>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/json.hpp>

#include "Manager.h"
#include "Shader.h"

#include "EngineSettings.hpp"

class GameWindow {
private:

	Manager threads;

	std::vector<int> size;
	
	Shader* shader;

	EngineSettings* settings;

public:

	std::string name;

	GLFWwindow* window;

	GameWindow(
		std::string name = "Window",
		std::vector<int> size = { 800, 600 }
	) {
		settings = new EngineSettings();

		SettingsReset();
	}

	bool SettingsReset() {

		this->size = settings->PathWindowSizeGetValue();
		this->name = settings->PathWindowNameGetValue();

		shader = new Shader(
			settings->PathShaderGetValue("VERT"),
			settings->PathShaderGetValue("FRAG")
		);
		return true;
	}

	bool Init(bool isFullScreen = false) {
		
		if (!glfwInit())
			return false;

		glewExperimental = GL_TRUE;
		//glewInit(); // not needed

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
		glfwMakeContextCurrent(window);
		//std::thread tRender(
		//	[&]() {
		//		Render();
		//	}
		//);
		//tRender.join();
		
		//threads.factory.push_back(tRender);

		while (!ShouldTerminate()) {
			


			//threads.factory[0].join();
			
			Render();
		}

	}

	bool ShouldTerminate() {
		return glfwWindowShouldClose(window);
	}




};