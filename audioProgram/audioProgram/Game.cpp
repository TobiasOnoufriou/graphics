#include "Game.h"
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

void Game::creating_plane() {
	//int plane_size = 512;
	GLfloat plane_vertices[] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};
	this->plane_verticies_indicies = {
		0,
	};



	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->plane_verticies_indicies.size() * sizeof(unsigned int), &this->plane_verticies_indicies[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	
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


	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	if (!loadShaderSource("vertex.vs", vertexShaderSource)) {
		std::cout << "Could not find vertex shader" << std::endl;
	}
	if (!loadShaderSource("fragment.fs", fragmentShaderSource)) {
		std::cout << "Could not find fragment shader" << std::endl;
	}
	const char *vertexSource = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexSource , NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//glm::mat4 = glm::translate();
	const char* fragmentSource = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	/**/

	creating_plane();

	//glfwSetKeyCallback(this->window, this->key_callback);
}
bool Game::loadShaderSource(const std::string& filename, std::string& out) {
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
}

void Game::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
void Game::game_loop() {
	
	this->processInput(window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glUseProgram(shaderProgram);
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES,
		this->plane_verticies_indicies.size(),
		GL_UNSIGNED_INT,
		(void*)0);

	
	glfwSwapBuffers(window);
	glfwPollEvents();
}

