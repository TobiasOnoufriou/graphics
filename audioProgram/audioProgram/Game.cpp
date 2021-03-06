#include "Game.h"

#include <glm.hpp>


Game::Game() {
	opengl_setup(800, 600);
}
Game::~Game() {
	glDeleteVertexArrays(1, &cubeVao);
	glDeleteVertexArrays(1, &lightVao);
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

		basicShader.loadShader("shaders/vertex.vs", 'V');
		basicShader.loadShader("shaders/fragment.fs", 'F');
		basicShader.compileShader();

		lampShader.loadShader("shaders/lampShader.fs", 'F');
		lampShader.loadShader("shaders/vertexLamp.vs", 'V');
		lampShader.compileShader();

		modelShader.loadShader("shaders/fragmentLoader.fs", 'F');
		modelShader.loadShader("shaders/modelLoader.vs", 'V');
		modelShader.compileShader();

		std::string path = "C:/Users/Tobias Onoufriou/source/repos/TobiasOnoufriou/graphics/audioProgram/audioProgram/Resource/nanosuit.obj";
		Model testModel(path);


		//MVP SETUP
		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		//Camera Setup
		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_STENCIL_TEST);
		
		game_loop(testModel);

		//planeSetup();
	
}
void Game::planeSetup() {
	GLfloat plane[] = {
		-0.5f, -0.3f, 0.0f,
		0.5f, -0.2f, 0.0f,
		1.f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};
	
	/*float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	/*float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};*/

	float verticesLight[] = {
	  -0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f,  0.5f, -0.5f,
	   0.5f,  0.5f, -0.5f,
	  -0.5f,  0.5f, -0.5f,
	  -0.5f, -0.5f, -0.5f,

	  -0.5f, -0.5f,  0.5f,
	   0.5f, -0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f,  0.5f,
	  -0.5f, -0.5f,  0.5f,

	  -0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f, -0.5f,
	  -0.5f, -0.5f, -0.5f,
	  -0.5f, -0.5f, -0.5f,
	  -0.5f, -0.5f,  0.5f,
	  -0.5f,  0.5f,  0.5f,

	   0.5f,  0.5f,  0.5f,
	   0.5f,  0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,

	  -0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f,  0.5f,
	   0.5f, -0.5f,  0.5f,
	  -0.5f, -0.5f,  0.5f,
	  -0.5f, -0.5f, -0.5f,

	  -0.5f,  0.5f, -0.5f,
	   0.5f,  0.5f, -0.5f,
	   0.5f,  0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f, -0.5f,
	};
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	unsigned int cubeVBO;
	glGenVertexArrays(1, &cubeVao);
	glGenBuffers(1, &cubeVBO);

	glBindVertexArray(cubeVao);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//Loading Multiple Textues/ or 1 texture.


	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture1);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("box.png", &width, &height, &nrChannels, 0);

	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
	}
	glGenTextures(1, &texture2);

	data = stbi_load("specular.png", &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture2);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}else {
		std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
	}

	glGenVertexArrays(1, &lightVao);
	glBindVertexArray(lightVao);
	//Doesn't need to be written again
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
}
void Game::processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = 0.01f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Game::game_loop(Model test) {
	while (!glfwWindowShouldClose(getWindow())) {
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};


		float currentFrame = glfwGetTime();
		//lastFrame = currentFrame;
		float deltaTime = currentFrame - lastFrame;
		processInput(window, deltaTime);
		//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		//trans = glm::translate(trans, glm::vec3(sin(0.1) * deltaTime, sin(0.1) * deltaTime,0.0));
		//trans = glm::rotate(trans, sin(glm::radians(90.0f)) * deltaTime, glm::vec3(1.0, 0.0, 1.0));
		//vec = trans * vec;

		//glEnable(GL_DEPTH_TEST);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilMask(0xFF);
		glStencilMask(0x00);
		//std::cout << greenValue << std::endl;
		//model = glm::rotate(model, deltaTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		/*glUseProgram(basicShader.getShaderProgram());
		glUniform1i(glGetUniformLocation(basicShader.getShaderProgram(), "material.diffuse"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(basicShader.getShaderProgram(), "material.specular"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		//Material Shaders*/


		//Light

		/*glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "light.position"), cameraPos.x,cameraPos.y,cameraPos.z);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "light.direction"), cameraFront.x, cameraFront.y, cameraFront.z);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "light.cutOff"), glm::cos(glm::radians(2.5f)));
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "light.outerCutOff"), glm::cos(glm::radians(15.0f)));
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);

		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "light.ambient"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "light.diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "light.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "light.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "light.quadratic"), 0.032f);*/

		/*glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "dirlight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "dirlight.ambient"), -0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "dirlight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "dirlight.specular"), 0.5f, 0.5f, 0.5f);
		//Point lights
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[0].diffuse"), 0.8f, 0.8f, 0.9f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[0].quadratic"), 0.032f);

		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[1].diffuse"), 0.8f, 0.8f, 0.9f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[1].quadratic"), 0.032f);
		//
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[2].diffuse"), 0.8f, 0.8f, 0.9f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[2].quadratic"), 0.032f);

		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[3].diffuse"), 0.8f, 0.8f, 0.9f);
		glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "pointLights[3].quadratic"), 0.032f);*/

		//Shader 
		//glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);
		/*
		int projLoc = glGetUniformLocation(basicShader.getShaderProgram(), "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		int viewLoc = glGetUniformLocation(basicShader.getShaderProgram(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//glm::mat4 model = glm::mat4(1.0f);

		glUniform1f(glGetUniformLocation(basicShader.getShaderProgram(), "material.shininess"), 32.0f);



		glBindVertexArray(cubeVao);
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			int modelLoc = glGetUniformLocation(basicShader.getShaderProgram(), "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//glUniform1i(glGetUniformLocation(basicShader.getShaderProgram(), "texture1"),0);
		//glUniform1i(glGetUniformLocation(basicShader.getShaderProgram(), "texture2"), 1);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture1);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);
		//float angle = 20.f;
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glUseProgram(lampShader.getShaderProgram());
		glUniformMatrix4fv(glGetUniformLocation(lampShader.getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(lampShader.getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		for (unsigned int i = 0; i < 4; i++) {
			//Drawing the small cube which is effectively the light source.
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			glUniformMatrix4fv(glGetUniformLocation(lampShader.getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(lightVao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/


		glUseProgram(modelShader.getShaderProgram());
		

		glUniform1i(glGetUniformLocation(modelShader.getShaderProgram(), "material.diffuse"), 0);

		glUniform1i(glGetUniformLocation(modelShader.getShaderProgram(), "material.specular"), 1);

		glUniform1f(glGetUniformLocation(modelShader.getShaderProgram(), "material.shininess"), 32.0f);
		
		glUniformMatrix4fv(glGetUniformLocation(modelShader.getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(glGetUniformLocation(modelShader.getShaderProgram(), "point.position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(modelShader.getShaderProgram(), "point.ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(modelShader.getShaderProgram(), "point.diffuse"), 0.8f, 0.8f, 0.9f);
		glUniform3f(glGetUniformLocation(modelShader.getShaderProgram(), "point.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(modelShader.getShaderProgram(), "point.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(modelShader.getShaderProgram(), "point.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(modelShader.getShaderProgram(), "point.quadratic"), 0.032f);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(modelShader.getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		test.Draw(modelShader);


		/*
		CAMERA DIRECTION
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
		*/

		//Camera Stuff
		float radius = 10.0f;
		float camX = sin(deltaTime) * radius;
		float camZ = cos(deltaTime) * radius;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		/*for (unsigned int i = 0; i <= 10; i++) {
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);

			//model = glm::mat4(1.0f);
			//model = glm::translate(model, lightPos);
			//model = glm::scale(model, glm::vec3(0.2f));


			float angle = deltaTime * sin(1000000.f) * 100 * i;

			model = glm::rotate(model, glm::radians(angle) , glm::vec3(1.0f, 0.3f, 0.5f));

			int modelLoc = glGetUniformLocation(basicShader.getShaderProgram(), "model");

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(),"objectColor"), 1.0f, 0.5f, 0.31f);
			glUniform3f(glGetUniformLocation(basicShader.getShaderProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);



			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

