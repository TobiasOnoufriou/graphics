#pragma once
#include "glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "glm\mat4x4.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Game {
private:
	GLFWwindow* window;
	GLenum res;
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLfloat plane_vertices[9];
	std::vector<unsigned int> plane_verticies_indicies;

public:
	Game();
	~Game();
	bool loadShaderSource(const std::string& filename, std::string& out);
	void opengl_setup(int width, int height);
	void error_callback(int error, const char* description);
	void processInput(GLFWwindow* window);
	void creating_plane();
	void game_loop();

	//Mutator
	GLFWwindow* getWindow() {
		return this->window;
	}

};