#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//Easy Shader loader so I can run multiple shaders



class shaderLoader {
private:
	int UIDLoc; //Uniform ID.
	GLuint vertexShader, fragmentShader, geometeryShader; //Shaders
	GLuint shaderProgram;
public:
	bool loadShader(const std::string& filename,char shaderType) {
		std::ifstream file;
		file.open(filename.c_str());
		if (!file) {
			std::cout << "Could not find shader source: " << filename << std::endl;
			return false;
		}
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		std::string out = stream.str();
		const char *shaderSource = out.c_str();
		int success;
		char infoLog[512];
		switch (shaderType) {
			case 'V':
				vertexShader = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertexShader, 1, &shaderSource, NULL);
				glCompileShader(vertexShader);
				glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
				}
				break;
			case 'F':
				fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragmentShader, 1, &shaderSource, NULL);
				glCompileShader(fragmentShader);
				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
				}
				break;
			case 'G':
				geometeryShader = glCreateShader(GL_GEOMETRY_SHADER);
				glShaderSource(geometeryShader, 1, &shaderSource, NULL);
				glCompileShader(geometeryShader);
				glGetShaderiv(geometeryShader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(geometeryShader, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
				}
				break;
		}		
	};
	void compileShader() {
		shaderProgram = glCreateProgram();
		if (vertexShader != NULL) {
			glAttachShader(shaderProgram, vertexShader);
			std::cout << "Compiled vertexShader shader";
		}
		if (fragmentShader != NULL) {
			glAttachShader(shaderProgram, fragmentShader);
			std::cout << "Compiled fragmentShader shader";
		}
		if (geometeryShader != NULL) {
			glAttachShader(shaderProgram, geometeryShader);
			std::cout << "Compiled geometeryShader shader";
		}
		glLinkProgram(shaderProgram);
	}
	int getUniformIDLoc(const char* uniformLoc) {
		UIDLoc = glGetUniformLocation(shaderProgram, uniformLoc);
		return this->UIDLoc;
	}
	GLuint getShaderProgram() {
		return this->shaderProgram;
	}	
};