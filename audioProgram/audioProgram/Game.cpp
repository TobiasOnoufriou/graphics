#include "Game.h"
Game::Game() {
	opengl_setup(800, 600);
}

Game::~Game() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

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
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(this->window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	//glfwSetKeyCallback(this->window, this->key_callback);
}

void Game::game_loop() {
	glViewport(0, 0, 800, 600);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(this->window);


	glfwSwapBuffers(window);
	glfwPollEvents();
}

