#pragma once
#include "glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include <iostream>
class Game {
private:
	GLFWwindow* window;
	GLenum res;
	GLuint vbo;

public:
	Game();
	~Game();
	void opengl_setup(int width, int height);
	void error_callback(int error, const char* description);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void game_loop();

	//Mutator
	GLFWwindow* getWindow() {
		return this->window;
	}

};