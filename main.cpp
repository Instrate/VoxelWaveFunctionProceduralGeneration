#define GLEW_STATIC
//#define GLFW_INCLUDE_NONE

#include <iostream>
#include <boost/algorithm/algorithm.hpp>
#include <algorithm>
#include <Windows.h>
//#include <GLFW/glfw3.h>

#include "GameWindow.h"


int main(int argc, char** argv) {


	GameWindow window = GameWindow();

	if (!window.Init()) {
		return -1;
	}
	
	window.Run();
	
    glfwTerminate();

	//std::cin.get();
	return EXIT_SUCCESS;
}