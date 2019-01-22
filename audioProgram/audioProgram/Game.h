#pragma once
#include "glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Game {
private:
	GLFWwindow* window;
	GLenum res;
	GLuint vbo;
	GLuint vao;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

public:
	Game();
	~Game();
	bool loadShaderSource(const std::string& filename, std::string& out);
	void opengl_setup(int width, int height);
	void error_callback(int error, const char* description);
	void processInput(GLFWwindow* window);
	void game_loop();

	//Mutator
	GLFWwindow* getWindow() {
		return this->window;
	}

};