#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//顶点数据
float vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
	0.8f,0.8f,0.0f
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//检查按键是否按下
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main() {
	int ret = glfwInit();//初始化glfw
	//设置主版本号和此版本号3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置profile类型---指定哪个更opengl来配置生成上下文
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800,800,"myOpengl",NULL,NULL);
	if (window == NULL) {
		printf("error");
		glfwTerminate();
		return -1;
	}
	//将这个窗口设置为主要的上下文
	glfwMakeContextCurrent(window);

	//初始化GLEW
	glewExperimental = true;  //无原因
	if (glewInit() != GLEW_OK) {
		printf("init glew error");
		glfwTerminate();
		return -1;
	}

	//渲染窗口尺寸
	//1,2设置左下角，右下角坐标，
	//3,4设置控制渲染窗口的宽度和高度（像素）
	glViewport(0, 0, 800, 600);
	//设置窗口变化时的大小。
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	/////////////////////////////////////////////////////顶点输入//////////////////////////////////////////////
	//VAO顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	//VBO顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);//生成一个缓冲，但是此时opengl并不知道对象类型是什么，所以需要进行绑定
	//绑定缓冲类型--顶点缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将顶点数据写入到顶点缓冲中
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices,GL_STATIC_DRAW);

	//顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//shader program---将vertexShader和fragmentShader连接成一个program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//设置解析顶点缓存对象的方式
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//循环渲染,
	while (!glfwWindowShouldClose(window)) {//检查glfw是否被退出
		//检查按键是否按下
		processInput(window);
		
		//渲染指令
		//glClearColor设置清空屏幕所用的颜色----状态设置函数
		//glClear函数清除颜色缓冲之后，屏幕会填充为glClearColor中的颜色。---状态使用函数
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//画三角形
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES,0,6);//画6个点

		//检查调用事件，交换缓存
		//双缓冲：前面缓存一张画面用于显示，后台会额外缓存另一张，当第一张结束，直接交换，效果上便不会有重新逐行绘制带来的闪屏。
		glfwSwapBuffers(window);//交换颜色缓存
		glfwPollEvents();//检查鼠标，键盘，更新窗口状态，并调用对应的回调函数。
	}

	//退出glfw
	glfwTerminate();
	return 0;
}