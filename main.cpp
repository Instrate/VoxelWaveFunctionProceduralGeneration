
//#define GLFW_INCLUDE_NONE

#include <iostream>

#include "GameWindow.h"

int main(int argc, char** argv) {
	GameWindow window = GameWindow();
	window.Run();
	glfwTerminate();
	//std::cin.get();
	return EXIT_SUCCESS;
}