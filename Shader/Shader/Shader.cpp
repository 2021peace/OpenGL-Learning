#pragma once
#include <iostream>

#define GLEW_STATIC 
#include<GL/glew.h>
#include<GLFW/glfw3.h>

float tringle[] = {
	-0.9f,0.0f,0.0f,  1.0f,0.0f,0.0f,
	0.9f,0.0f,0.0f,   0.0f,1.0f,0.0f,
	0.0f,0.9f,0.0f,	  0.0f,0.0f,1.0f
};

//顶点着色器
const char* vertexShaderSource =
"#version 330 core \n"
"layout(location = 0) in vec3 apos; \n"
"layout(location = 1) in vec3 acolor;\n"
"out vec3 vertexColor;\n"
"void main(){ \n"
"gl_Position = vec4(apos,1.0);\n"
"vertexColor = acolor;\n"
"}\n";

//片段着色器
const char* fragmentShaderSource =
"#version 330 core          \n"
"in vec3 vertexColor; \n"
"out vec4 FragColor;\n"
"void main(){ \n"
"FragColor = vec4(vertexColor,1.0);\n"
"}\n";


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置opengl为核心模式

	GLFWwindow* window = glfwCreateWindow(800, 800, "myWidget", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = true;  //尝试加载全部opengl扩展
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		printf("init glew error");
		fprintf(stderr, "glew初始化失败：%s\n", glewGetErrorString(err));
		glfwTerminate();
		return -1;
	}

	unsigned int VAO;
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tringle), tringle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int successVertexShader;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertexShader);
	if (!successVertexShader)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int successfragmentShader;
	char infoLog2[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successfragmentShader);
	if (!successfragmentShader)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	}


	//链接着色器
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	while (!glfwWindowShouldClose(window)) {
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//双缓存
		glfwSwapBuffers(window);//交换颜色缓存
		glfwPollEvents();//监察事件
	}

	glfwTerminate();
	return 0;
}