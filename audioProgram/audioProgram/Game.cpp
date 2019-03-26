#include "Game.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
Game::Game() {
	opengl_setup(800, 600);
}
Game::~Game() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void Game::opengl_setup(int width, int height) {


	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(width, height, "Audio Test", nullptr, nullptr);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	basicShader.loadShader("vertex.vs", 'V');
	basicShader.loadShader("fragment.fs", 'F');

	basicShader.compileShader();

	planeSetup();
	
}

void Game::planeSetup() {

	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	/*GLfloat texCoords[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.5f, 1.0f, 0.0f
	};*/

	/*int width, height, nrChannels;
	unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	
	stbi_image_free(data);*/
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/*GLint postAttrib = glGetAttribLocation(shaderProgram, "pos");
	glEnableVertexAttribArray(postAttrib);*/


	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}
/*bool Game::loadShaderSource(const std::string& filename, std::string& out) {
	std::ifstream file;
	file.open(filename.c_str());
	if (!file) {
		return false;
	}
	std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	out = stream.str();
	return true;
}*/
void Game::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
void Game::game_loop() {
	
	float currentFrame = glfwGetTime();
	//lastFrame = currentFrame;
	float deltaTime = currentFrame - lastFrame;
	
	this->processInput(window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*GLint loc = glGetUniformLocation(geometryShader, "u_time");
	lastFrame += 0.0000001;
	glUniform1f(loc, lastFrame);*/
	
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	glm::vec4 newColor(0.4f, 0.5f, 0.3f, 1.0f);
	glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "newColor"), newColor.x, newColor.y, newColor.z);
	glUseProgram(basicShader.getShaderProgram());
	
	glfwSwapBuffers(window);
	glfwPollEvents();
	
	
}

