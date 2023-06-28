#include <iostream>

#define GLEW_STATIC 
#include<GL/glew.h>
#include<GLFW/glfw3.h>

    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

//GLSL顶点着色器的源代码
const char* vertexShaderSource =
"#version 330 core \n"
"layout(location = 0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";

//片段着色器的源代码
const char* fragmentShaderSource =
"#version 330 core          \n"
"out vec4 FragColor; \n"
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }\n";

int main() {
	//初始化Glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置opengl为核心模式

	GLFWwindow* window = glfwCreateWindow(800,800,"myWindow",NULL,NULL);
	if (window == NULL) {
		printf("glfw初始化错误");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//绑定上下文
	

	//初始化GLEW
	glewExperimental = true;  //尝试加载全部opengl扩展
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		printf("init glew error");
		fprintf(stderr,"glew初始化失败：%s\n", glewGetErrorString(err));
		glfwTerminate();
		return -1;
	}

	//创建VAO
	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	//创建VBO
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	//绑定VAO
	//配置VAO[0];
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//配置VAO[1];
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

	//链接着色器
	unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

	//循环渲染
	while (!glfwWindowShouldClose(window)) {

		//渲染指令
		//状态设置函数
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//状态应用函数
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
        // 第一个三角形
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
		//第二个三角形
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//双缓存
		glfwSwapBuffers(window);//交换颜色缓存
		glfwPollEvents();//监察事件
	}
	//删除内存
	glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}