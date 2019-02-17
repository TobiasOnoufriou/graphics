#include "Game.h"
#include <glm.hpp>

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


	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);


	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	std::string geometryShaderSource;
	if (!loadShaderSource("vertex.vs", vertexShaderSource)) {
		std::cout << "Could not find vertex shader" << std::endl;
	}
	if (!loadShaderSource("fragment.fs", fragmentShaderSource)) {
		std::cout << "Could not find fragment shader" << std::endl;
	}
	if (!loadShaderSource("geometryShader.gs", geometryShaderSource)) {
		std::cout << "Could not find geometry shader" << std::endl;
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
	
	const char* fragmentSource = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	shaderProgram = glCreateProgram();


	const char* geometrySource = geometryShaderSource.c_str();
	glShaderSource(geometryShader, 1, &geometrySource, NULL);
	glCompileShader(geometryShader);
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, geometryShader);
	glLinkProgram(shaderProgram);
	

	planeSetup();
	
}

void Game::planeSetup() {
	glm::mat4 view = glm::mat4(1.0f);
	
	GLfloat plane[] = {
		-0.5f, -0.3f, 0.0f,
		0.5f, -0.2f, 0.0f,
		1.f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);
	
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLint postAttrib = glGetAttribLocation(shaderProgram, "pos");
	glEnableVertexAttribArray(postAttrib);
	glVertexAttribPointer(postAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	
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
	
	float currentFrame = glfwGetTime();
	//lastFrame = currentFrame;
	float deltaTime = currentFrame - lastFrame;
	
	this->processInput(window);

	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	


	GLint loc = glGetUniformLocation(geometryShader, "u_time");
	lastFrame += 0.0000001;
	glUniform1f(loc, lastFrame);
	
	

	glUseProgram(shaderProgram);
	
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 4);

	
	glfwSwapBuffers(window);
	glfwPollEvents();
	
	
}

