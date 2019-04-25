#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderLoader.h"
#include "glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include "assimp/include/material.h"
#include "Model.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Game {
private:
	GLFWwindow* window;

	GLenum res;
	GLuint vbo;
	GLuint cubeVao, lightVao;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLuint geometryShader;
	unsigned int texture1,texture2;
	glm::mat4 proj, model, view;
	glm::vec3 cameraPos, cameraFront, cameraUp; //= glm::vec3(0.0f, 0.0f, 3.0f);
	//= glm::vec3(0.0f, 0.0f, -1.0f);
	float lastFrame;
	shaderLoader basicShader;
	shaderLoader lampShader;
	shaderLoader modelShader;
public:
	Game();
	~Game();
	bool loadShaderSource(const std::string& filename, std::string& out);
	void opengl_setup(int width, int height);
	void error_callback(int error, const char* description);
	void processInput(GLFWwindow* window, float deltaTime);
	void game_loop(Model test);
	void planeSetup();

	//Mutator
	GLFWwindow* getWindow() {
		return this->window;
	}

};